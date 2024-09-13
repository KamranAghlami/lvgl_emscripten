#include "ui/lvgl/canvas.h"

#define _lv_color(c) lv_color_make((c).red(), (c).green(), (c).blue())
#define _lv_color32(c) lv_color32_make((c).red(), (c).green(), (c).blue(), (c).alpha())

#include <algorithm>

#include <lvgl.h>

namespace ui
{
    namespace lvgl
    {
        canvas::canvas(object &parent) : image(lv_canvas_create(parent.lv_object()))
        {
        }

        canvas &canvas::set_buffer(void *buffer, int32_t width, int32_t height, color::format format)
        {
            lv_canvas_set_buffer(lv_object(), buffer, width, height, static_cast<lv_color_format_t>(format));

            return *this;
        }

        canvas &canvas::set_pixel(int32_t x, int32_t y, const color &c, uint8_t opacity)
        {
            lv_canvas_set_px(lv_object(), x, y, _lv_color(c), opacity);

            return *this;
        }

        canvas &canvas::set_palette(uint8_t index, const color32 &c)
        {
            lv_canvas_set_palette(lv_object(), index, _lv_color32(c));

            return *this;
        }

        color32 canvas::get_pixel(int32_t x, int32_t y)
        {
            const auto c = lv_canvas_get_px(lv_object(), x, y);

            return color32(c.red, c.green, c.blue, c.alpha);
        }

        const void *canvas::get_buf()
        {
            return lv_canvas_get_buf(lv_object());
        }

        canvas &canvas::fill_bg(const color &c, uint8_t opacity)
        {
            lv_canvas_fill_bg(lv_object(), _lv_color(c), opacity);

            return *this;
        }

        canvas &canvas::set_draw_buf(lv_draw_buf_t *draw_buffer)
        {
            lv_canvas_set_draw_buf(lv_object(), draw_buffer);

            return *this;
        }

        lv_draw_buf_t *canvas::get_draw_buf()
        {
            return lv_canvas_get_draw_buf(lv_object());
        }

        canvas &canvas::copy_buf(int32_t x, int32_t y, lv_draw_buf_t *buffer)
        {
            const auto draw_buf = get_draw_buf();

            const lv_area_t source_area = {
                .x1 = x,
                .y1 = y,
                .x2 = std::min(x + buffer->header.w, static_cast<int32_t>(draw_buf->header.w)) - 1,
                .y2 = std::min(y + buffer->header.h, static_cast<int32_t>(draw_buf->header.h)) - 1,
            };

            lv_canvas_copy_buf(lv_object(), &source_area, buffer, nullptr);

            return *this;
        }
    }
}