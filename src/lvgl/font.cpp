#include "lvgl/font.h"

#include <cassert>

#include <lvgl.h>

namespace lvgl
{
    font::font(const char *path, const int32_t size)
        : mp_font(lv_tiny_ttf_create_file(path, size)),
          is_static(false)
    {
    }

    font::font(const lv_font_t *font)
        : mp_font(font),
          is_static(true)
    {
    }

    font::~font()
    {
        if (is_static)
            return;

        lv_tiny_ttf_destroy(const_cast<lv_font_t *>(mp_font));
    }

    font &font::set_size(int32_t size)
    {
        if (is_static)
            return *this;

        lv_tiny_ttf_set_size(const_cast<lv_font_t *>(mp_font), size);

        return *this;
    }

    const lv_font_t *font::lv_font() const
    {
        return mp_font;
    }
}
