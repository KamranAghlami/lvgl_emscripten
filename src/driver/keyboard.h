#pragma once

#include <emscripten/bind.h>
#include <emscripten/html5.h>
#include <lvgl.h>

#include "lvgl/group.h"
#include "lvgl/object.h"

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

        void set_group(lvgl::group &grp);

    private:
        keyboard();

        void show_keyboard();
        void hide_keyboard();

        EM_BOOL on_key_down(int type, const EmscriptenKeyboardEvent *keyboard_event, void *user_data);

        uint32_t map_control_key(const EmscriptenKeyboardEvent *keyboard_event);
        void on_keyboard_read(lv_indev_data_t *data);

        emscripten::val m_input_element = emscripten::val::null();
        lv_indev_t *mp_device = nullptr;
        state m_last_state = {};
    };
}