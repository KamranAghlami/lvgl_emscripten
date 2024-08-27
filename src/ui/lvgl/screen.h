#pragma once

#include "ui/lvgl/object.h"

namespace ui
{
    namespace lvgl
    {
        class screen : public object
        {
        public:
            static screen &active();

            screen();

            screen &load();
        };
    }
}