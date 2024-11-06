#include "driver/keyboard.h"

#include <cstring>

namespace driver
{
    keyboard::keyboard()
    {
        {
            emscripten::val document = emscripten::val::global("document");

            m_input_element = document.call<emscripten::val>("createElement", std::string("input"));
            m_input_element.set("type", "text");
            m_input_element.set("contenteditable", "true");

            m_input_element["style"].set("position", "absolute");
            m_input_element["style"].set("left", 0);
            m_input_element["style"].set("top", 0);
            m_input_element["style"].set("opacity", 0);
            m_input_element["style"].set("display", "");
            m_input_element["style"].set("z-index", -2);

            document["body"].call<void>("appendChild", m_input_element);
        }

        auto on_key_down = [](int type, const EmscriptenKeyboardEvent *mouse_event, void *user_data)
        {
            return static_cast<keyboard *>(user_data)->on_key_down(type, mouse_event, user_data);
        };

        emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_TRUE, on_key_down);

        mp_device = lv_indev_create();

        auto on_keyboard_read = [](lv_indev_t *device, lv_indev_data_t *data)
        {
            static_cast<keyboard *>(lv_indev_get_driver_data(device))->on_keyboard_read(data);
        };

        lv_indev_set_type(mp_device, LV_INDEV_TYPE_KEYPAD);
        lv_indev_set_read_cb(mp_device, on_keyboard_read);
        lv_indev_set_mode(mp_device, LV_INDEV_MODE_EVENT);
        lv_indev_set_driver_data(mp_device, this);
    }

    keyboard::~keyboard()
    {
        lv_indev_delete(mp_device);
    }

    void keyboard::set_group(lv_group_t *group)
    {
        auto g = lv_indev_get_group(mp_device);

        if (g)
            lv_group_set_focus_cb(g, nullptr);

        lv_indev_set_group(mp_device, group);

        focus(lv_group_get_focused(group));

        auto on_focus = [](lv_group_t *group)
        {
            get().focus(lv_group_get_focused(group));
        };

        lv_group_set_focus_cb(group, on_focus);
    }

    void keyboard::show_keyboard()
    {
        m_input_element.call<void>("focus");
    }

    void keyboard::hide_keyboard()
    {
        m_input_element.call<void>("blur");
    }

    void keyboard::focus(lv_obj_t *obj)
    {
        if (!obj)
        {
            hide_keyboard();

            return;
        }

        if (lv_obj_get_class(obj) == &lv_textarea_class || lv_obj_has_flag(obj, LV_OBJ_FLAG_USER_4))
            show_keyboard();
        else
            hide_keyboard();
    }

    EM_BOOL keyboard::on_key_down(int type, const EmscriptenKeyboardEvent *keyboard_event, void *user_data)
    {
        const bool is_combination = keyboard_event->ctrlKey ||
                                    keyboard_event->altKey ||
                                    keyboard_event->metaKey;

        if (is_combination || keyboard_event->key[1])
        {
            m_last_state.key = map_control_key(keyboard_event);

            if (!m_last_state.key)
                return EM_FALSE;
        }
        else
            m_last_state.key = keyboard_event->key[0];

        m_last_state.pressed = true;

        lv_indev_read(mp_device);

        m_last_state.pressed = false;

        lv_indev_read(mp_device);

        return EM_TRUE;
    }

    uint32_t keyboard::map_control_key(const EmscriptenKeyboardEvent *keyboard_event)
    {
        if (!strcmp("ArrowUp", keyboard_event->key))
            return LV_KEY_UP;

        if (!strcmp("ArrowDown", keyboard_event->key))
            return LV_KEY_DOWN;

        if (!strcmp("ArrowRight", keyboard_event->key))
            return LV_KEY_RIGHT;

        if (!strcmp("ArrowLeft", keyboard_event->key))
            return LV_KEY_LEFT;

        if (!strcmp("Escape", keyboard_event->key))
            return LV_KEY_ESC;

        if (!strcmp("Delete", keyboard_event->key))
            return LV_KEY_DEL;

        if (!strcmp("Backspace", keyboard_event->key))
            return LV_KEY_BACKSPACE;

        if (!strcmp("Enter", keyboard_event->key))
            return LV_KEY_ENTER;

        if (!strcmp("Tab", keyboard_event->key))
        {
            if (keyboard_event->shiftKey)
                return LV_KEY_PREV;
            else
                return LV_KEY_NEXT;
        }

        if (!strcmp("Home", keyboard_event->key))
            return LV_KEY_HOME;

        if (!strcmp("End", keyboard_event->key))
            return LV_KEY_END;

        return 0;
    }

    void keyboard::on_keyboard_read(lv_indev_data_t *data)
    {
        data->key = m_last_state.key;
        data->state = m_last_state.pressed ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
    }
}