#pragma once

#include <unordered_map>

#include "driver/memory.h"
#include "lvgl/font.h"
#include "lvgl/color.h"

extern "C"
{
    struct lv_theme_t;
    struct lv_obj_t;
}

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
        color get_color_primary();
        color get_color_secondary();

        theme &activate();

        lv_theme_t *lv_theme();

    protected:
        virtual void apply_callback(lv_theme_t *t, lv_obj_t *o) = 0;

    private:
        static theme &from_lv_theme(lv_theme_t *lv_thm);

        static driver::memory::unordered_map<lv_theme_t *, theme *> s_themes;

        lv_theme_t *mp_theme;
    };
}
