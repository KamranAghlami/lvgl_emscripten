#pragma once

#include <emscripten/html5.h>
#include <lvgl.h>

namespace input
{
    class mouse
    {
    public:
        struct state
        {
            int x;
            int y;
            bool pressed;
        };

        static mouse &get()
        {
            static mouse instance;

            return instance;
        };

        ~mouse();

        mouse(const mouse &) = delete;
        mouse(mouse &&) = delete;
        mouse &operator=(const mouse &) = delete;
        mouse &operator=(mouse &&) = delete;

    private:
        mouse();

        EM_BOOL on_mouse_down(int type, const EmscriptenMouseEvent *mouse_event, void *user_data);
        EM_BOOL on_mouse_up(int type, const EmscriptenMouseEvent *mouse_event, void *user_data);
        EM_BOOL on_mouse_move(int type, const EmscriptenMouseEvent *mouse_event, void *user_data);

        void on_mouse_read(lv_indev_data_t *data);

        lv_indev_t *mp_device = nullptr;
        state m_last_state = {};
    };
}
