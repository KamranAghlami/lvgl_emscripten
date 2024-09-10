#pragma once

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
            font() {}
            ~font() {}

            font(const font &) = delete;
            font(font &&) = delete;
            font &operator=(const font &) = delete;
            font &operator=(font &&) = delete;

            lv_font_t *lv_font() const;

        private:
            lv_font_t *mp_font;
        };
    }
}
