#pragma once

#include <lvgl.h>

#include "ui/lvgl/lvgl.h"
#include "io/filesystem.h"

namespace ui
{
    class widget_thingy : public lvgl::object
    {
    public:
        widget_thingy(object &parent) : object(parent), m_image(*this), m_label(*this)
        {
            auto on_fetch = [this](const std::string &path)
            {
                m_image.set_source(path.c_str());
            };

            io::filesystem::get().fetch("image/icon.png", on_fetch);

            m_image.align(alignment::CENTER);
            m_label.align(alignment::CENTER);

            auto on_pressed = [this](lvgl::event &e)
            {
                recolor();
            };

            add_event_callback(lvgl::event::code::PRESSED, on_pressed);

            recolor();
        }

        template <typename... Args>
        widget_thingy &set_text_fmt(const char *fmt, Args &&...args)
        {
            m_label.set_text_fmt(fmt, std::forward<Args>(args)...);

            return *this;
        }

    private:
        void recolor()
        {
            const auto c = lvgl::color::random();

            m_style.set_background_color(c);
            m_style.set_text_color(c.negative());

            add_style(m_style, lvgl::object::part::MAIN | lvgl::object::state::DEFAULT);
        }

        lvgl::style m_style;
        lvgl::image m_image;
        lvgl::label m_label;
    };
}
