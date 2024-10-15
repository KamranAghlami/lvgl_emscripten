#pragma once

#include "lvgl/object.h"
#include "lvgl/style.h"

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

        explicit image(lv_obj_t *lv_obj);

        virtual ~image();

        image &set_source(const void *source);
        image &set_offset_x(int32_t offset_x);
        image &set_offset_y(int32_t offset_y);
        image &set_rotation(int32_t rotation);
        image &set_pivot(int32_t pivot_x, int32_t pivot_y);
        image &set_scale(uint32_t scale);
        image &set_scale_x(uint32_t scale_x);
        image &set_scale_y(uint32_t scale_y);
        image &set_blend_mode(style::blend_mode mode);
        image &set_antialiasing(bool enable);
        image &set_inner_alignment(image_alignment alignment);
        const void *get_source();
        int32_t get_offset_x();
        int32_t get_offset_y();
        int32_t get_rotation();
        int32_t get_scale();
        int32_t get_scale_x();
        int32_t get_scale_y();
        style::blend_mode get_blend_mode();
        bool get_antialiasing();
        image_alignment get_inner_alignment();
    };
}
