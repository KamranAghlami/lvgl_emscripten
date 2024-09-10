#pragma once

#include <cstdint>

namespace ui
{
    namespace lvgl
    {
        class color
        {
        public:
            color() : m_blue(0), m_green(0), m_red(0) {}
            color(uint8_t red, uint8_t green, uint8_t blue) : m_blue(blue), m_green(green), m_red(red) {}

            uint8_t blue() const { return m_blue; }
            uint8_t green() const { return m_green; }
            uint8_t red() const { return m_red; }

            color negative() const { return color(0xFF - m_red, 0xFF - m_green, 0xFF - m_blue); }

        private:
            uint8_t m_blue;
            uint8_t m_green;
            uint8_t m_red;
        };
    }
}