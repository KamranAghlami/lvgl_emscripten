#pragma once

#include "ui/lvgl/object.h"
#include "ui/lvgl/style.h"

namespace ui
{
    namespace lvgl
    {
        class image : public object
        {
        public:
            enum class image_alignment : uint8_t
            {
                DEFAULT,
                TOP_LEFT,
                TOP_MID,
                TOP_RIGHT,
                BOTTOM_LEFT,
                BOTTOM_MID,
                BOTTOM_RIGHT,
                LEFT_MID,
                RIGHT_MID,
                CENTER,
                AUTO_TRANSFORM,
                STRETCH,
                TILE,
            };

            image(object &parent);
            ~image();

            image &set_src(const void *src);
            image &set_offset_x(int32_t x);
            image &set_offset_y(int32_t y);
            image &set_rotation(int32_t angle);
            image &set_pivot(int32_t x, int32_t y);
            image &set_scale(uint32_t zoom);
            image &set_scale_x(uint32_t zoom);
            image &set_scale_y(uint32_t zoom);
            image &set_blend_mode(style::blend_mode mode);
            image &set_antialias(bool antialias);
            image &set_inner_align(image_alignment alignment);
            const void *get_src();
            int32_t get_offset_x();
            int32_t get_offset_y();
            int32_t get_rotation();
            int32_t get_scale();
            int32_t get_scale_x();
            int32_t get_scale_y();
            style::blend_mode get_blend_mode();
            bool get_antialias();
            image_alignment get_inner_align();
        };
    }
}
