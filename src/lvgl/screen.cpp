#include "lvgl/screen.h"

#include <lvgl.h>

namespace lvgl
{
    screen &screen::active()
    {
        return static_cast<screen &>(object::from_lv_object(lv_scr_act()));
    };

    screen::screen() : object(lv_obj_create(nullptr))
    {
    }

    screen &screen::load()
    {
        lv_screen_load(lv_object());

        return *this;
    }
}
