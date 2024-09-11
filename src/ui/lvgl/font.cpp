#include "ui/lvgl/font.h"

#include <lvgl.h>

namespace ui
{
    namespace lvgl
    {
        font::font(const std::string &path, int32_t size) : mp_font(lv_tiny_ttf_create_file(path.c_str(), size))
        {
        }

        font::~font()
        {
            lv_tiny_ttf_destroy(mp_font);
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
