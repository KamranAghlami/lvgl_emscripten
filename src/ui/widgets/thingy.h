#pragma once

#include <lvgl.h>

namespace ui
{
    namespace widgets
    {
        namespace thingy
        {
            lv_obj_t *create(lv_obj_t *parent);

            void set_text_fmt(lv_obj_t *obj, const char *fmt, ...);
        }
    }
}