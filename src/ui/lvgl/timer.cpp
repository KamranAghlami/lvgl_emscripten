#include "ui/lvgl/timer.h"

#include <lvgl.h>

namespace ui
{
    namespace lvgl
    {
        timer::timer(const callback &cb, uint32_t period, void *user_data) : m_callback(cb), mp_user_data(user_data)
        {
            auto on_timeout = [](lv_timer_t *lv_timer)
            {
                auto t = static_cast<timer *>(lv_timer_get_user_data(lv_timer));

                t->m_callback(*t);
            };

            mp_timer = lv_timer_create(on_timeout, period, this);

            lv_timer_set_auto_delete(static_cast<lv_timer_t *>(mp_timer), false);
        }

        timer::~timer()
        {
            lv_timer_delete(static_cast<lv_timer_t *>(mp_timer));
        }

        timer &timer::pause()
        {
            lv_timer_pause(static_cast<lv_timer_t *>(mp_timer));

            return *this;
        }

        timer &timer::resume()
        {
            lv_timer_resume(static_cast<lv_timer_t *>(mp_timer));

            return *this;
        }

        timer &timer::set_callback(const callback &cb)
        {
            m_callback = cb;

            return *this;
        }

        timer &timer::set_period(uint32_t period)
        {
            lv_timer_set_period(static_cast<lv_timer_t *>(mp_timer), period);

            return *this;
        }

        timer &timer::set_user_data(void *user_data)
        {
            mp_user_data = user_data;

            return *this;
        }

        timer &timer::set_repeat_count(int32_t repeat_count)
        {
            lv_timer_set_repeat_count(static_cast<lv_timer_t *>(mp_timer), repeat_count);

            return *this;
        }

        timer &timer::ready()
        {
            lv_timer_ready(static_cast<lv_timer_t *>(mp_timer));

            return *this;
        }

        timer &timer::reset()
        {
            lv_timer_reset(static_cast<lv_timer_t *>(mp_timer));

            return *this;
        }

        bool timer::paused()
        {
            return lv_timer_get_paused(static_cast<lv_timer_t *>(mp_timer));
        }

        const timer::callback &timer::get_callback()
        {
            return m_callback;
        }

        void *timer::get_user_data()
        {
            return mp_user_data;
        }
    }
}