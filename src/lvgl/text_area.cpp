#include "lvgl/text_area.h"

#include <lvgl.h>

namespace lvgl
{
    text_area::text_area(object &parent)
        : object(lv_textarea_create(parent.lv_object())),
          m_label(lv_textarea_get_label(lv_object()))
    {
    }

    text_area::~text_area()
    {
    }

    text_area &text_area::add_char(uint32_t c)
    {
        lv_textarea_add_char(lv_object(), c);

        return *this;
    }

    text_area &text_area::add_text(const char *text)
    {
        lv_textarea_add_text(lv_object(), text);

        return *this;
    }

    text_area &text_area::delete_char()
    {
        lv_textarea_delete_char(lv_object());

        return *this;
    }

    text_area &text_area::delete_char_forward()
    {
        lv_textarea_delete_char_forward(lv_object());

        return *this;
    }

    text_area &text_area::set_text(const char *text)
    {
        lv_textarea_set_text(lv_object(), text);

        return *this;
    }

    text_area &text_area::set_placeholder_text(const char *text)
    {
        lv_textarea_set_placeholder_text(lv_object(), text);

        return *this;
    }

    text_area &text_area::set_cursor_position(int32_t position)
    {
        lv_textarea_set_cursor_pos(lv_object(), position);

        return *this;
    }

    text_area &text_area::set_cursor_click_position(bool enable)
    {
        lv_textarea_set_cursor_click_pos(lv_object(), enable);

        return *this;
    }

    text_area &text_area::set_password_mode(bool enable)
    {
        lv_textarea_set_password_mode(lv_object(), enable);

        return *this;
    }

    text_area &text_area::set_password_bullet(const char *bullet)
    {
        lv_textarea_set_password_bullet(lv_object(), bullet);

        return *this;
    }

    text_area &text_area::set_one_line(bool enable)
    {
        lv_textarea_set_one_line(lv_object(), enable);

        return *this;
    }

    text_area &text_area::set_accepted_chars(const char *list)
    {
        lv_textarea_set_accepted_chars(lv_object(), list);

        return *this;
    }

    text_area &text_area::set_max_length(uint32_t length)
    {
        lv_textarea_set_max_length(lv_object(), length);

        return *this;
    }

    text_area &text_area::set_insert_replace(const char *text)
    {
        lv_textarea_set_insert_replace(lv_object(), text);

        return *this;
    }

    text_area &text_area::set_text_selection(bool enable)
    {
        lv_textarea_set_text_selection(lv_object(), enable);

        return *this;
    }

    text_area &text_area::set_password_show_time(uint32_t time)
    {
        lv_textarea_set_password_show_time(lv_object(), time);

        return *this;
    }

    text_area &text_area::set_align(style::text_alignment alignment)
    {
        lv_textarea_set_align(lv_object(), static_cast<lv_text_align_t>(alignment));

        return *this;
    }

    const char *text_area::get_text()
    {
        return lv_textarea_get_text(lv_object());
    }

    const char *text_area::get_placeholder_text()
    {
        return lv_textarea_get_placeholder_text(lv_object());
    }

    lvgl::label &text_area::get_label()
    {
        return m_label;
    }

    uint32_t text_area::get_cursor_position()
    {
        return lv_textarea_get_cursor_pos(lv_object());
    }

    bool text_area::get_cursor_click_position()
    {
        return lv_textarea_get_cursor_click_pos(lv_object());
    }

    bool text_area::get_password_mode()
    {
        return lv_textarea_get_password_mode(lv_object());
    }

    const char *text_area::get_password_bullet()
    {
        return lv_textarea_get_password_bullet(lv_object());
    }

    bool text_area::get_one_line()
    {
        return lv_textarea_get_one_line(lv_object());
    }

    const char *text_area::get_accepted_chars()
    {
        return lv_textarea_get_accepted_chars(lv_object());
    }

    uint32_t text_area::get_max_length()
    {
        return lv_textarea_get_max_length(lv_object());
    }

    bool text_area::text_is_selected()
    {
        return lv_textarea_text_is_selected(lv_object());
    }

    bool text_area::get_text_selection()
    {
        return lv_textarea_get_text_selection(lv_object());
    }

    uint32_t text_area::get_password_show_time()
    {
        return lv_textarea_get_password_show_time(lv_object());
    }

    uint32_t text_area::get_current_char()
    {
        return lv_textarea_get_current_char(lv_object());
    }

    text_area &text_area::clear_selection()
    {
        lv_textarea_clear_selection(lv_object());

        return *this;
    }

    text_area &text_area::cursor_right()
    {
        lv_textarea_cursor_right(lv_object());

        return *this;
    }

    text_area &text_area::cursor_left()
    {
        lv_textarea_cursor_left(lv_object());

        return *this;
    }

    text_area &text_area::cursor_down()
    {
        lv_textarea_cursor_down(lv_object());

        return *this;
    }

    text_area &text_area::cursor_up()
    {
        lv_textarea_cursor_up(lv_object());

        return *this;
    }

}
