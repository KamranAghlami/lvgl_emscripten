#pragma once

#include <cstdint>

namespace ui
{
    namespace lvgl
    {
        class style
        {
        public:
            using selector = uint32_t;

            enum class state : uint16_t
            {
                DEFAULT = 0x0000,
                CHECKED = 0x0001,
                FOCUSED = 0x0002,
                FOCUS_KEY = 0x0004,
                EDITED = 0x0008,
                HOVERED = 0x0010,
                PRESSED = 0x0020,
                SCROLLED = 0x0040,
                DISABLED = 0x0080,
                USER_1 = 0x1000,
                USER_2 = 0x2000,
                USER_3 = 0x4000,
                USER_4 = 0x8000,
                ANY = 0xFFFF,
            };

            enum class part : uint32_t
            {
                MAIN = 0x000000,
                SCROLLBAR = 0x010000,
                INDICATOR = 0x020000,
                KNOB = 0x030000,
                SELECTED = 0x040000,
                ITEMS = 0x050000,
                CURSOR = 0x060000,
                CUSTOM_FIRST = 0x080000,
                ANY = 0x0F0000,
            };

            enum class blend_mode : uint8_t
            {
                NORMAL,
                ADDITIVE,
                SUBTRACTIVE,
                MULTIPLY,
            };

            style();
            ~style();

        private:
            void *mp_style;

            friend class object;
        };
    }
}
