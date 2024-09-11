#include "ui/lvgl/theme.h"

#include <lvgl.h>
#include <src/themes/lv_theme_private.h>

#include "ui/lvgl/lvgl.h"

namespace ui
{
    namespace lvgl
    {
        theme::theme() : mp_theme(static_cast<lv_theme_t *>(lvgl::malloc(sizeof(lv_theme_t))))
        {
            lv_theme_t *default_theme = lv_display_get_theme(NULL);

            if (default_theme)
            {
                *mp_theme = *default_theme;

                lv_theme_set_parent(mp_theme, default_theme);
            }
            else
                memset(mp_theme, 0, sizeof(lv_theme_t));

            static auto apply_cb = [](lv_theme_t *t, lv_obj_t *o)
            {
                static_cast<theme *>(t->user_data)->apply_callback(t, o);
            };

            lv_theme_set_apply_cb(mp_theme, apply_cb);

            mp_theme->user_data = this;
        }

        theme::~theme()
        {
            lvgl::free(mp_theme);
        }

        void theme::activate()
        {
            lv_display_set_theme(NULL, mp_theme);
        }

        lv_theme_t *theme::lv_theme()
        {
            return mp_theme;
        }
    }
}
