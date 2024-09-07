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
            ~button();
        };
    }
}
