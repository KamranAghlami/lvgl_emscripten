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

        style &style::set_background_color(const color &c)
        {
            lv_style_set_bg_color(lv_style, lv_color(c));

            return *this;
        }

        style &style::set_text_color(const color &c)
        {
            lv_style_set_text_color(lv_style, lv_color(c));

            return *this;
        }

        style &style::set_pad_top(int32_t v)
        {
            lv_style_set_pad_top(lv_style, v);

            return *this;
        }

        style &style::set_pad_bottom(int32_t v)
        {
            lv_style_set_pad_bottom(lv_style, v);

            return *this;
        }

        style &style::set_pad_left(int32_t v)
        {
            lv_style_set_pad_left(lv_style, v);

            return *this;
        }

        style &style::set_pad_right(int32_t v)
        {
            lv_style_set_pad_right(lv_style, v);

            return *this;
        }

        style &style::set_pad_row(int32_t v)
        {
            lv_style_set_pad_row(lv_style, v);

            return *this;
        }

        style &style::set_pad_column(int32_t v)
        {
            lv_style_set_pad_column(lv_style, v);

            return *this;
        }

        style &style::set_margin_top(int32_t v)
        {
            lv_style_set_margin_top(lv_style, v);

            return *this;
        }

        style &style::set_margin_bottom(int32_t v)
        {
            lv_style_set_margin_bottom(lv_style, v);

            return *this;
        }

        style &style::set_margin_left(int32_t v)
        {
            lv_style_set_margin_left(lv_style, v);

            return *this;
        }

        style &style::set_margin_right(int32_t v)
        {
            lv_style_set_margin_right(lv_style, v);

            return *this;
        }
    };
}