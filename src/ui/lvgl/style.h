#pragma once

#include <cstdint>

#include <ui/lvgl/color.h>

namespace ui
{
    namespace lvgl
    {
        class style
        {
        public:
            enum class blend_mode : uint8_t
            {
                NORMAL,
                ADDITIVE,
                SUBTRACTIVE,
                MULTIPLY,
            };

            style();
            ~style();

            style(const style &) = delete;
            style(style &&) = delete;
            style &operator=(const style &) = delete;
            style &operator=(style &&) = delete;

            style &set_background_color(const color &c);
            style &set_text_color(const color &c);
            style &set_pad_top(int32_t v);
            style &set_pad_bottom(int32_t v);
            style &set_pad_left(int32_t v);
            style &set_pad_right(int32_t v);
            style &set_pad_row(int32_t v);
            style &set_pad_column(int32_t v);
            style &set_margin_top(int32_t v);
            style &set_margin_bottom(int32_t v);
            style &set_margin_left(int32_t v);
            style &set_margin_right(int32_t v);

        private:
            void *mp_style;

            friend class object;
        };
    }
}
