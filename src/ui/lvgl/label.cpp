#include "ui/lvgl/label.h"

#include <lvgl.h>

namespace ui
{
    namespace lvgl
    {
        label::label(object &parent) : object(lv_label_create(parent.lv_object()))
        {
        }

        label::~label()
        {
        }

        label &label::set_text(const char *text)
        {
            lv_label_set_text(lv_object(), text);

            return *this;
        }

        label &label::set_text_static(const char *text)
        {
            lv_label_set_text_static(lv_object(), text);

            return *this;
        }

        label &label::set_long_mode(long_mode mode)
        {
            lv_label_set_long_mode(lv_object(), static_cast<lv_label_long_mode_t>(mode));

            return *this;
        }

        label &label::set_text_selection_start(uint32_t index)
        {
            lv_label_set_text_selection_start(lv_object(), index);

            return *this;
        }

        label &label::set_text_selection_end(uint32_t index)
        {
            lv_label_set_text_selection_end(lv_object(), index);

            return *this;
        }

        char *label::get_text()
        {
            return lv_label_get_text(lv_object());
        }

        label::long_mode label::get_long_mode()
        {
            return static_cast<long_mode>(lv_label_get_long_mode(lv_object()));
        }

        uint32_t label::get_text_selection_start()
        {
            return lv_label_get_text_selection_start(lv_object());
        }

        uint32_t label::get_text_selection_end()
        {
            return lv_label_get_text_selection_end(lv_object());
        }

        label &label::insert_text(uint32_t position, const char *text)
        {
            lv_label_ins_text(lv_object(), position, text);

            return *this;
        }

        label &label::cut_text(uint32_t position, uint32_t count)
        {
            lv_label_cut_text(lv_object(), position, count);

            return *this;
        }
    }
}