#pragma once

#include <lvgl.h>

#include "ui/lvgl/lvgl.h"

namespace ui
{
    class label_thingy : public lvgl::object
    {
    public:
        label_thingy(object &parent) : object(parent), m_label(*this)
        {
            m_label.align(alignment::CENTER);

            auto on_pressed = [this](lvgl::event &e)
            {
                recolor();
            };

            add_event_callback(lvgl::event::code::PRESSED, on_pressed);

            recolor();
        }

        template <typename... Args>
        label_thingy &set_text_fmt(const char *fmt, Args &&...args)
        {
            m_label.set_text_fmt(fmt, std::forward<Args>(args)...);

            return *this;
        }

    private:
        void recolor()
        {
            auto color = lv_color_make(lv_rand(0, 0xFF), lv_rand(0, 0xFF), lv_rand(0, 0xFF));
            auto color_negative = lv_color_make(0xFF - color.red, 0xFF - color.green, 0xFF - color.blue);

            lv_obj_set_style_bg_color(lv_object(), color, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(m_label.lv_object(), color_negative, LV_PART_MAIN | LV_STATE_DEFAULT);
        }

        lvgl::label m_label;
    };
}
