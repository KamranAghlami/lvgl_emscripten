#include "lvgl/color.h"

#define _lv_color lv_color_make(m_red, m_green, m_blue)

#include <lvgl.h>

#include "lvgl/lvgl.h"

namespace lvgl
{
    color color::random()
    {
        return color(lvgl::random(0, 0xFF), lvgl::random(0, 0xFF), lvgl::random(0, 0xFF));
    };

    color color::darkened(uint8_t v) const
    {
        auto darkened = lv_color_darken(_lv_color, v);

        return color(darkened.red, darkened.green, darkened.blue);
    }

    color color::negative() const
    {
        return color(0xFF - m_red, 0xFF - m_green, 0xFF - m_blue);
    }
}
