#include "io/keyboard.h"

#include <cstring>

namespace io
{
    keyboard::keyboard()
    {
        auto on_key_down = [](int type, const EmscriptenKeyboardEvent *mouse_event, void *user_data)
        {
            return static_cast<keyboard *>(user_data)->on_key_down(type, mouse_event, user_data);
        };

        emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_FALSE, on_key_down);

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
        lv_indev_set_group(mp_device, group);
    }

    EM_BOOL keyboard::on_key_down(int type, const EmscriptenKeyboardEvent *keyboard_event, void *user_data)
    {
        m_last_state.key = keyboard_event->key[0];
        m_last_state.pressed = true;

        if (keyboard_event->key[1] != '\0')
            if (!(m_last_state.key = map_control_key(keyboard_event)))
                return EM_FALSE;

        lv_indev_read(mp_device);

        m_last_state.pressed = false;

        lv_indev_read(mp_device);

        return EM_FALSE;
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