#pragma once

#pragma once

#include <emscripten/html5.h>
#include <lvgl.h>

#include "event/handler.h"
#include "event/window.h"

namespace output
{
    class display : public event::handler<display>
    {
    public:
        static display &get()
        {
            static display instance;

            return instance;
        };

        ~display();

        display(const display &) = delete;
        display(display &&) = delete;
        display &operator=(const display &) = delete;
        display &operator=(display &&) = delete;

        void set_scaling(float scaling);

    private:
        display();

        bool on_size_change(const event::window::size_changed &event);

        void update_size();
        void set_bitmap(const int x1, const int y1, const int x2, const int y2, uint8_t *buffer);

        int m_width = 0;
        int m_height = 0;
        float m_scaling = 1.0f;

        void *mp_draw_buf_1 = nullptr;
        void *mp_draw_buf_2 = nullptr;
        lv_display_t *mp_display = nullptr;
    };
}
