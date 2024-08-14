#include "application/application.h"

#include <assert.h>
#include <sstream>

#include <emscripten.h>
#include <emscripten/html5.h>

static application *s_instance = nullptr;

application::application()
{
    assert(s_instance == nullptr);

    s_instance = this;

    lv_init();

    auto tick_get_cb = []() -> uint32_t
    {
        return emscripten_get_now();
    };

    lv_tick_set_cb(tick_get_cb);

    subscribe(&application::on_size_change);

    {
        double width;
        double height;

        emscripten_get_element_css_size("canvas", &width, &height);

        event::dispatcher::global().dispatch(event::window::size_changed(width, height));
    }

    auto on_resize = [](int event_type, const EmscriptenUiEvent *ui_event, void *user_data) -> EM_BOOL
    {
        double width;
        double height;

        emscripten_get_element_css_size("canvas", &width, &height);

        event::dispatcher::global().dispatch(event::window::size_changed(width, height));

        return EM_FALSE;
    };

    emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_FALSE, on_resize);

    auto on_orientation_change = [](int event_type, const EmscriptenOrientationChangeEvent *orientation_change_event, void *user_data) -> EM_BOOL
    {
        double width;
        double height;

        emscripten_get_element_css_size("canvas", &width, &height);

        event::dispatcher::global().dispatch(event::window::size_changed(width, height));

        return EM_FALSE;
    };

    emscripten_set_orientationchange_callback(this, EM_FALSE, on_orientation_change);

    auto on_update = [](double time, void *user_data) -> EM_BOOL
    {
        static const auto app = static_cast<application *>(user_data);

        float timestep = time - app->m_previous_timestamp;
        app->m_previous_timestamp = time;

        if (timestep < 0.0f)
            timestep = 0.0f;

        app->update(timestep);

        lv_timer_handler();

        return EM_TRUE;
    };

    emscripten_request_animation_frame_loop(on_update, this);
}

application::~application()
{
    lv_display_delete(mp_display);
    free(mp_draw_buf_2);
    free(mp_draw_buf_1);

    lv_deinit();
}

bool application::on_size_change(const event::window::size_changed &event)
{
    int width = event.m_width * m_scaling;
    int height = event.m_height * m_scaling;

    if (width == m_width && height == m_height)
        return true;

    m_width = width;
    m_height = height;

    emscripten_set_canvas_element_size("canvas", m_width, m_height);

    size_t buffer_size = (LV_COLOR_DEPTH / 8) * m_width * m_height * 0.1f;

    if (mp_draw_buf_1)
        free(mp_draw_buf_1);

    mp_draw_buf_1 = malloc(buffer_size);

    if (mp_draw_buf_2)
        free(mp_draw_buf_2);

    mp_draw_buf_2 = malloc(buffer_size);

    if (!mp_display)
    {
        mp_display = lv_display_create(m_width, m_height);

        auto flush_cb = [](lv_display_t *display, const lv_area_t *area, uint8_t *pix_map)
        {
            auto app = static_cast<application *>(lv_display_get_user_data(display));

            app->set_bitmap(area->x1, area->y1, area->x2, area->y2, pix_map);

            lv_display_flush_ready(static_cast<lv_display_t *>(app->mp_display));
        };

        lv_display_set_flush_cb(mp_display, flush_cb);
        lv_display_set_user_data(mp_display, this);
    }

    lv_display_set_resolution(mp_display, m_width, m_height);
    lv_display_set_buffers(mp_display, mp_draw_buf_1, mp_draw_buf_2, buffer_size, LV_DISPLAY_RENDER_MODE_PARTIAL);

    return true;
}

void application::set_bitmap(const int x1, const int y1, const int x2, const int y2, uint8_t *buffer)
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