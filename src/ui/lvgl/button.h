#pragma once

#include "ui/lvgl/object.h"

namespace ui
{
    namespace lvgl
    {
        class button : public object
        {
        public:
            button(object &parent);

            explicit button(lv_obj_t *lv_obj);

            ~button();
        };
    }
}
