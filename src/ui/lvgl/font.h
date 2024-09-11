#pragma once

#include <string>

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
            font(const std::string &path, int32_t size = 14);
            ~font();

            font(const font &) = delete;
            font(font &&) = delete;
            font &operator=(const font &) = delete;
            font &operator=(font &&) = delete;

            void set_size(int32_t size);

            lv_font_t *lv_font() const;

        private:
            lv_font_t *mp_font;
        };
    }
}
