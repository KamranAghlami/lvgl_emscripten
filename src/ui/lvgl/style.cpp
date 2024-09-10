#include "ui/lvgl/style.h"

#define lv_style static_cast<lv_style_t *>(mp_style)
#define lv_color(c)         \
    lv_color_t              \
    {                       \
        .blue = c.blue(),   \
        .green = c.green(), \
        .red = c.red()      \
    }

#include <lvgl.h>

namespace ui
{
    namespace lvgl
    {
        style::style() : mp_style(lv_malloc(sizeof(lv_style_t)))
        {
            lv_style_init(lv_style);
        }

        style::~style()
        {
            lv_style_reset(lv_style);

            lv_free(mp_style);
        }

        style &style::set_background_color(const color &c, const selector sel)
        {
            lv_style_set_bg_color(lv_style, lv_color(c));

            return *this;
        }

        style &style::set_text_color(const color &c, const selector sel)
        {
            lv_style_set_text_color(lv_style, lv_color(c));

            return *this;
        }
    };
}