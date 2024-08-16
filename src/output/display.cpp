#include "output/display.h"

namespace output
{
    display::display()
    {
        mp_display = lv_display_create(m_width, m_height);

        auto flush_cb = [](lv_display_t *disp, const lv_area_t *area, uint8_t *pix_map)
        {
            auto app = static_cast<display *>(lv_display_get_user_data(disp));

            app->set_bitmap(area->x1, area->y1, area->x2, area->y2, pix_map);

            lv_display_flush_ready(static_cast<lv_display_t *>(app->mp_display));
        };

        lv_display_set_flush_cb(mp_display, flush_cb);
        lv_display_set_user_data(mp_display, this);

        subscribe(&display::on_size_change);

        update_size();

        auto on_resize = [](int event_type, const EmscriptenUiEvent *ui_event, void *user_data) -> EM_BOOL
        {
            static_cast<display *>(user_data)->update_size();

            return EM_FALSE;
        };

        emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_FALSE, on_resize);

        auto on_orientation_change = [](int event_type, const EmscriptenOrientationChangeEvent *orientation_change_event, void *user_data) -> EM_BOOL
        {
            static_cast<display *>(user_data)->update_size();

            return EM_FALSE;
        };

        emscripten_set_orientationchange_callback(this, EM_FALSE, on_orientation_change);
    }

    display::~display()
    {
        lv_display_delete(mp_display);

        free(mp_draw_buf_2);
        free(mp_draw_buf_1);
    }

    void display::set_scaling(float scaling)
    {
        m_scaling = scaling;

        update_size();
    }

    bool display::on_size_change(const event::window::size_changed &event)
    {
        m_width = event.m_width;
        m_height = event.m_height;

        emscripten_set_canvas_element_size("canvas", m_width, m_height);

        const size_t buffer_size = (LV_COLOR_DEPTH / 8) * m_width * m_height * 0.1f;

        if (mp_draw_buf_1)
            free(mp_draw_buf_1);

        mp_draw_buf_1 = malloc(buffer_size);

        if (mp_draw_buf_2)
            free(mp_draw_buf_2);

        mp_draw_buf_2 = malloc(buffer_size);

        lv_display_set_resolution(mp_display, m_width, m_height);
        lv_display_set_buffers(mp_display, mp_draw_buf_1, mp_draw_buf_2, buffer_size, LV_DISPLAY_RENDER_MODE_PARTIAL);

        return true;
    }

    void display::update_size()
    {
        double width = 0.0;
        double height = 0.0;

        emscripten_get_element_css_size("canvas", &width, &height);

        int new_width = width * m_scaling;
        int new_height = height * m_scaling;

        if (new_width == m_width && new_height == m_height)
            return;

        event::dispatcher::global().dispatch(event::window::size_changed(new_width, new_height));
    }

    void display::set_bitmap(const int x1, const int y1, const int x2, const int y2, uint8_t *buffer)
    {
        const int width = x2 - x1 + 1;
        const int height = y2 - y1 + 1;
        const int size = width * height * 4;

        for (size_t i = 0; i < size; i += 4)
            std::swap(buffer[i + 0], buffer[i + 2]);

        EM_ASM(
            {
                const canvas = document.getElementById('canvas');
                const context = canvas.getContext('2d', {willReadFrequently : true});
                const image = context.createImageData($2, $3);

                image.data.set(Module.HEAPU8.subarray($5, $5 + $4));

                context.putImageData(image, $0, $1);
            },
            x1, y1, width, height, size, buffer);
    }
}