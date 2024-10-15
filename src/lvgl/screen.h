#pragma once

#include "lvgl/object.h"

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
