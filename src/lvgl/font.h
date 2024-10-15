#pragma once

#include <cstdint>

extern "C"
{
    struct lv_font_t;
}

namespace lvgl
{
    class font
    {
    public:
        font(const char *path, const int32_t size);
        explicit font(const lv_font_t *font);
        ~font();

        font(const font &) = delete;
        font(font &&) = delete;
        font &operator=(const font &) = delete;
        font &operator=(font &&) = delete;

        font &set_size(int32_t size);

        const lv_font_t *lv_font() const;

    private:
        const lv_font_t *mp_font;

        bool is_static;
    };
}
