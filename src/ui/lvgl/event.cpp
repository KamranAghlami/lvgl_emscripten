#include "ui/lvgl/event.h"

#include <lvgl.h>

#include "ui/lvgl/object.h"

namespace ui
{
    namespace lvgl
    {
        event::code event::get_code()
        {
            auto e = static_cast<lv_event_t *>(mp_event);

            return static_cast<event::code>(lv_event_get_code(e));
        }

        void *event::user_data()
        {
            return mp_user_data;
        }

        void *event::parameter()
        {
            auto e = static_cast<lv_event_t *>(mp_event);

            return lv_event_get_param(e);
        }

        object &event::current_target_object()
        {
            auto e = static_cast<lv_event_t *>(mp_event);

            return object::from_lv_object(lv_event_get_current_target_obj(e));
        }

        object &event::target_object()
        {
            auto e = static_cast<lv_event_t *>(mp_event);

            return object::from_lv_object(lv_event_get_target_obj(e));
        }

        uint32_t event::get_key()
        {
            return lv_event_get_key(static_cast<lv_event_t *>(mp_event));
        }

        event::event(void *lv_event) : mp_event(lv_event),
                                       mp_user_data(static_cast<event::descriptor *>(lv_event_get_user_data(static_cast<lv_event_t *>(lv_event)))->m_user_data)
        {
        }
    }
}