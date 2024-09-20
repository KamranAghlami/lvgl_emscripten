#pragma once

#include <unordered_map>

#include "ui/lvgl/font.h"
#include "ui/lvgl/color.h"
#include "ui/lvgl/memory.h"

extern "C"
{
    struct lv_theme_t;
    struct lv_obj_t;
}

namespace ui
{
    namespace lvgl
    {
        class theme
        {
        public:
            static void set_active(theme &thm);
            static theme *get_active();

            theme();
            virtual ~theme();

            theme(const theme &) = delete;
            theme(theme &&) = delete;
            theme &operator=(const theme &) = delete;
            theme &operator=(theme &&) = delete;

            theme &set_parent(theme &parent);
            font *get_font_small();
            font *get_font_normal();
            font *get_font_large();
            color get_color_primary();
            color get_color_secondary();

            theme &activate();

            lv_theme_t *lv_theme();

        protected:
            virtual void apply_callback(lv_theme_t *t, lv_obj_t *o) = 0;

        private:
            static theme &from_lv_theme(lv_theme_t *lv_thm);

            static std::unordered_map<lv_theme_t *, theme *, std::hash<lv_theme_t *>, std::equal_to<lv_theme_t *>, allocator<std::pair<lv_theme_t *const, theme *>>> s_themes;

            lv_theme_t *mp_theme;
        };
    }
}
