#pragma once

#include "ui/lvgl/image.h"
#include "ui/lvgl/color.h"

extern "C"
{
    struct lv_draw_buf_t;
}

namespace ui
{
    namespace lvgl
    {
        class canvas : public image
        {
        public:
            canvas(object &parent);

            canvas &set_buffer(void *buffer, int32_t width, int32_t height, color::format format);
            canvas &set_pixel(int32_t x, int32_t y, const color &c, uint8_t opacity = 0xff);
            canvas &set_palette(uint8_t index, const color32 &c);

            color32 get_pixel(int32_t x, int32_t y);
            const void *get_buf();

            canvas &fill_bg(const color &c, uint8_t opacity = 0xff);

        protected:
            canvas &set_draw_buf(lv_draw_buf_t *draw_buffer);

            lv_draw_buf_t *get_draw_buf();

            canvas &copy_buf(int32_t x, int32_t y, lv_draw_buf_t *buffer);
        };
    }
}