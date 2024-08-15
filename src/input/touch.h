#pragma once

#include <emscripten/html5.h>
#include <lvgl.h>

namespace input
{
    class touch
    {
    public:
        struct state
        {
            decltype(EmscriptenTouchPoint::targetX) x;
            decltype(EmscriptenTouchPoint::targetY) y;
            bool present;
        };

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

    private:
        touch();

        EM_BOOL on_touch_start(int type, const EmscriptenTouchEvent *touch_event, void *user_data);
        EM_BOOL on_touch_move(int type, const EmscriptenTouchEvent *touch_event, void *user_data);
        EM_BOOL on_touch_end(int type, const EmscriptenTouchEvent *touch_event, void *user_data);
        EM_BOOL on_touch_cancel(int type, const EmscriptenTouchEvent *touch_event, void *user_data);

        void on_touch_read(lv_indev_data_t *data);

        lv_indev_t *mp_device = nullptr;
        state m_last_state = {};
    };
}
