#include "ui/lvgl/button.h"

#include <lvgl.h>

namespace ui
{
    namespace lvgl
    {
        button::button(object &parent) : object(lv_button_create(parent.lv_object()))
        {
        }

        button::~button()
        {
        }
    }
}