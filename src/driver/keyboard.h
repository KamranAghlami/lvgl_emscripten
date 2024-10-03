#pragma once

#include <emscripten/html5.h>
#include <lvgl.h>

#include "ui/lvgl/group.h"

namespace driver
{
    class keyboard
    {
    public:
        struct state
        {
            uint32_t key;
            bool pressed;
        };

        static keyboard &get()
        {
            static keyboard instance;

            return instance;
        };

        ~keyboard();

        keyboard(const keyboard &) = delete;
        keyboard(keyboard &&) = delete;
        keyboard &operator=(const keyboard &) = delete;
        keyboard &operator=(keyboard &&) = delete;

        void set_group(ui::lvgl::group &group);

    private:
        keyboard();

        EM_BOOL on_key_down(int type, const EmscriptenKeyboardEvent *keyboard_event, void *user_data);

        uint32_t map_control_key(const EmscriptenKeyboardEvent *keyboard_event);
        void on_keyboard_read(lv_indev_data_t *data);

        lv_indev_t *mp_device = nullptr;
        state m_last_state = {};
    };
}