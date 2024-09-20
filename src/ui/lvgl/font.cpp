#include "ui/lvgl/font.h"

#include <cassert>

#include <lvgl.h>

namespace ui
{
    namespace lvgl
    {
        std::unordered_map<lv_font_t *, font *, std::hash<lv_font_t *>, std::equal_to<lv_font_t *>, allocator<std::pair<lv_font_t *const, font *>>> font::s_fonts;

        font &font::from_lv_font(const lv_font_t *lv_fnt)
        {
            auto it = s_fonts.find(const_cast<lv_font_t *>(lv_fnt));

            assert(it != s_fonts.end());

            return *it->second;
        }

        font::font(const char *path, int32_t size) : mp_font(lv_tiny_ttf_create_file(path, size))
        {
            s_fonts.emplace(mp_font, this);
        }

        font::~font()
        {
            lv_tiny_ttf_destroy(mp_font);

            s_fonts.erase(mp_font);
        }

        void font::set_size(int32_t size)
        {
            lv_tiny_ttf_set_size(mp_font, size);
        }

        lv_font_t *font::lv_font() const
        {
            return mp_font;
        }
    }
}
