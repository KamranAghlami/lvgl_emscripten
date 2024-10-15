#pragma once

#include "lvgl/object.h"
#include "lvgl/label.h"
#include "style.h"

namespace lvgl
{
    class text_area : public object
    {
    public:
        text_area(object &parent);

        ~text_area();

        text_area &add_char(uint32_t c);
        text_area &add_text(const char *text);
        text_area &delete_char();
        text_area &delete_char_forward();

        text_area &set_text(const char *text);
        text_area &set_placeholder_text(const char *text);
        text_area &set_cursor_position(int32_t position);
        text_area &set_cursor_click_position(bool enable);
        text_area &set_password_mode(bool enable);
        text_area &set_password_bullet(const char *bullet);
        text_area &set_one_line(bool enable);
        text_area &set_accepted_chars(const char *list);
        text_area &set_max_length(uint32_t length);
        text_area &set_insert_replace(const char *text);
        text_area &set_text_selection(bool enable);
        text_area &set_password_show_time(uint32_t time);
        text_area &set_align(style::text_alignment alignment);

        const char *get_text();
        const char *get_placeholder_text();
        lvgl::label &get_label();
        uint32_t get_cursor_position();
        bool get_cursor_click_position();
        bool get_password_mode();
        const char *get_password_bullet();
        bool get_one_line();
        const char *get_accepted_chars();
        uint32_t get_max_length();
        bool text_is_selected();
        bool get_text_selection();
        uint32_t get_password_show_time();
        uint32_t get_current_char();

        text_area &clear_selection();
        text_area &cursor_right();
        text_area &cursor_left();
        text_area &cursor_down();
        text_area &cursor_up();

    private:
        lvgl::label m_label;
    };
}
