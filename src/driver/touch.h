#pragma once

#include <unordered_map>

#include <emscripten/html5.h>
#include <lvgl.h>

#include "lvgl/memory.h"

namespace driver
{
    class touch
    {
    public:
        static touch &get()
        {
            static touch instance;

            return instance;
        };

        ~touch();

        touch(const touch &) = delete;
        touch(touch &&) = delete;
        touch &operator=(const touch &) = delete;
        touch &operator=(touch &&) = delete;

        void set_scaling(float scaling);

    private:
        class device
        {
        public:
            device(int identifier);
            ~device();

            device(const device &) = delete;
            device(device &&) = delete;
            device &operator=(const device &) = delete;
            device &operator=(device &&) = delete;

            int get_identifier();

            void set_x(const int x);
            void set_y(const int y);
            void set_pressed(const bool pressed);

            void read();

        private:
            struct state
            {
                int x;
                int y;
                bool pressed;
            };

            void on_touch_read(lv_indev_data_t *data);

            int m_identifier = 0;
            lv_indev_t *mp_indev = nullptr;
            state m_state = {};
        };

        touch();

        EM_BOOL on_touch_start(int type, const EmscriptenTouchEvent *touch_event, void *user_data);
        EM_BOOL on_touch_move(int type, const EmscriptenTouchEvent *touch_event, void *user_data);
        EM_BOOL on_touch_end(int type, const EmscriptenTouchEvent *touch_event, void *user_data);
        EM_BOOL on_touch_cancel(int type, const EmscriptenTouchEvent *touch_event, void *user_data);

        device &get_device(int identifier);
        void release_device(device &dev);

        float m_scaling = 1.0f;

        lvgl::unordered_map<int, device *> m_devices;
    };
}
