#include "ui/lvgl/screen.h"

#include <lvgl.h>

namespace ui
{
    namespace lvgl
    {
        screen &screen::active()
        {
            return static_cast<screen &>(object::from_lv_object(lv_scr_act()));
        };

        screen::screen() : object(static_cast<object *>(nullptr))
        {
        }

        screen &screen::load()
        {
            lv_screen_load(static_cast<lv_obj_t *>(lv_object()));

            return *this;
        }
    }
}