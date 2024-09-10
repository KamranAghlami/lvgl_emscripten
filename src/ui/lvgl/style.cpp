#include "ui/lvgl/style.h"

#include <lvgl.h>

namespace ui
{
    namespace lvgl
    {
        style::style() : mp_style(lv_malloc(sizeof(lv_style_t)))
        {
            lv_style_init(static_cast<lv_style_t *>(mp_style));
        }

        style::~style()
        {
            lv_style_reset(static_cast<lv_style_t *>(mp_style));
            lv_free(mp_style);
        }
    };
}