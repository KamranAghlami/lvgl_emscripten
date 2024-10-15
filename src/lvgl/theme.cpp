#include "lvgl/theme.h"

#include <cstring>
#include <cassert>

#include <lvgl.h>
#include <src/themes/lv_theme_private.h>

namespace lvgl
{
    unordered_map<lv_theme_t *, theme *> theme::s_themes;

    void theme::set_active(theme &thm)
    {
        lv_display_set_theme(NULL, thm.mp_theme);
    }

    theme *theme::get_active()
    {
        auto lv_thm = lv_display_get_theme(NULL);

        return lv_thm ? &from_lv_theme(lv_thm) : nullptr;
    }

    theme &theme::from_lv_theme(lv_theme_t *lv_thm)
    {
        auto it = s_themes.find(lv_thm);

        assert(it != s_themes.end());

        return *it->second;
    }

    theme::theme() : mp_theme(static_cast<lv_theme_t *>(lvgl::malloc(sizeof(lv_theme_t))))
    {
        lv_theme_t *default_theme = lv_display_get_theme(NULL);

        if (default_theme)
        {
            *mp_theme = *default_theme;

            lv_theme_set_parent(mp_theme, default_theme);
        }
        else
            lvgl::memset(mp_theme, 0, sizeof(lv_theme_t));

        static auto apply_cb = [](lv_theme_t *t, lv_obj_t *o)
        {
            static_cast<theme *>(t->user_data)->apply_callback(t, o);
        };

        lv_theme_set_apply_cb(mp_theme, apply_cb);

        mp_theme->user_data = this;

        s_themes.emplace(mp_theme, this);
    }

    theme::~theme()
    {
        lvgl::free(mp_theme);

        s_themes.erase(mp_theme);
    }

    theme &theme::set_parent(theme &parent)
    {
        lv_theme_set_parent(mp_theme, parent.mp_theme);

        return *this;
    }

    color theme::get_color_primary()
    {
        return color(mp_theme->color_primary.red, mp_theme->color_primary.green, mp_theme->color_primary.blue);
    }

    color theme::get_color_secondary()
    {
        return color(mp_theme->color_secondary.red, mp_theme->color_secondary.green, mp_theme->color_secondary.blue);
    }

    theme &theme::activate()
    {
        lv_display_set_theme(NULL, mp_theme);

        return *this;
    }

    lv_theme_t *theme::lv_theme()
    {
        return mp_theme;
    }
}
