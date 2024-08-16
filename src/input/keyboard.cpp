#include "input/keyboard.h"

namespace input
{
    keyboard::keyboard()
    {
        auto on_key_down = [](int type, const EmscriptenKeyboardEvent *mouse_event, void *user_data)
        {
            return static_cast<keyboard *>(user_data)->on_key_down(type, mouse_event, user_data);
        };

        emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_FALSE, on_key_down);

        auto on_key_up = [](int type, const EmscriptenKeyboardEvent *mouse_event, void *user_data)
        {
            return static_cast<keyboard *>(user_data)->on_key_up(type, mouse_event, user_data);
        };

        emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_FALSE, on_key_up);

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
        lv_indev_read(mp_device);

        return EM_FALSE;
    }

    EM_BOOL keyboard::on_key_up(int type, const EmscriptenKeyboardEvent *keyboard_event, void *user_data)
    {
        lv_indev_read(mp_device);

        return EM_FALSE;
    }

    void keyboard::on_keyboard_read(lv_indev_data_t *data)
    {
    }
}