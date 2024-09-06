#pragma once

#include <functional>

extern "C"
{
    struct lv_timer_t;
}

namespace ui
{
    namespace lvgl
    {
        class timer
        {
        public:
            using callback = std::function<void(timer &)>;

            timer(const callback &cb, uint32_t period, void *user_data = nullptr);
            ~timer();

            timer(const timer &) = delete;
            timer(timer &&) = delete;
            timer &operator=(const timer &) = delete;
            timer &operator=(timer &&) = delete;

            timer &pause();
            timer &resume();
            timer &set_callback(const callback &cb);
            timer &set_period(uint32_t period);
            timer &set_user_data(void *user_data);
            timer &set_repeat_count(int32_t repeat_count);
            timer &ready();
            timer &reset();

            bool paused();
            const callback &get_callback();
            void *get_user_data();

        private:
            lv_timer_t *mp_timer;
            callback m_callback;
            void *mp_user_data;
        };
    }
}
