#pragma once

#include <unordered_map>

#include "ui/lvgl/memory.h"

extern "C"
{
    struct lv_font_t;
}

namespace ui
{
    namespace lvgl
    {
        class font
        {
        public:
            font(const char *path, int32_t size = 14);
            ~font();

            font(const font &) = delete;
            font(font &&) = delete;
            font &operator=(const font &) = delete;
            font &operator=(font &&) = delete;

            void set_size(int32_t size);

            lv_font_t *lv_font() const;

        private:
            static font &from_lv_font(const lv_font_t *lv_fnt);

            static std::unordered_map<lv_font_t *, font *, std::hash<lv_font_t *>, std::equal_to<lv_font_t *>, allocator<std::pair<lv_font_t *const, font *>>> s_fonts;

            lv_font_t *mp_font;

            friend class theme;
        };
    }
}
