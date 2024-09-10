#include "ui/lvgl/color.h"

#include <lvgl.h>

namespace ui
{
    namespace lvgl
    {
        color color::random() { return color(lv_rand(0, 0xFF), lv_rand(0, 0xFF), lv_rand(0, 0xFF)); };

        color color::negative() const { return color(0xFF - m_red, 0xFF - m_green, 0xFF - m_blue); }
    }
}