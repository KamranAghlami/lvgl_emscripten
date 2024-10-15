#include "lvgl/button.h"

#include <lvgl.h>

namespace lvgl
{
    button::button(object &parent) : object(lv_button_create(parent.lv_object()))
    {
    }

    button::button(lv_obj_t *lv_obj) : object(lv_obj)
    {
    }

    button::~button()
    {
    }
}
