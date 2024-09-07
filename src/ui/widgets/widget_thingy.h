#pragma once

#include <lvgl.h>

#include "ui/lvgl/lvgl.h"
#include "io/filesystem.h"

namespace ui
{
    class widget_thingy : public lvgl::object
    {
    public:
        widget_thingy(object &parent) : object(parent), m_image(*this)
        {
            auto on_fetch = [this](const std::string &path)
            {
                m_image.set_source(path.c_str());
            };

            io::filesystem::get().fetch("image/icon.png", on_fetch);

            m_image.align(alignment::CENTER);

            auto on_pressed = [this](lvgl::event &e)
            {
                recolor();
            };

            add_event_callback(lvgl::event::code::PRESSED, on_pressed);

            recolor();
        }

    private:
        void recolor()
        {
            auto color = lv_color_make(lv_rand(0, 0xFF), lv_rand(0, 0xFF), lv_rand(0, 0xFF));

            lv_obj_set_style_bg_color(lv_object(), color, LV_PART_MAIN | LV_STATE_DEFAULT);
        }

        lvgl::image m_image;
    };
}
