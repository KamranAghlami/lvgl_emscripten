#pragma once

#include <cstdint>

#include "ui/lvgl/object.h"

namespace ui
{
    namespace lvgl
    {
        class style
        {
        public:
            enum class blend_mode
            {
                NORMAL,
                ADDITIVE,
                SUBTRACTIVE,
                MULTIPLY,
            };

            class selector
            {
            public:
                selector(object::state state) : m_value(static_cast<uint16_t>(state)) {}
                selector(object::part part) : m_value(static_cast<uint32_t>(part)) {}

                operator uint32_t() const { return m_value; }

            private:
                uint32_t m_value;
            };

            style();
            ~style();

        private:
            void *mp_style;
        };
    }
}
