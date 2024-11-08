#include "lvgl/event.h"

#include <lvgl.h>

#include "lvgl/object.h"

namespace lvgl
{
    event::code event::get_code()
    {
        return static_cast<event::code>(lv_event_get_code(mp_event));
    }

    void *event::get_user_data()
    {
        return mp_user_data;
    }

    void *event::get_parameter()
    {
        return lv_event_get_param(mp_event);
    }

    object &event::get_current_target_object()
    {
        return object::from_lv_object(lv_event_get_current_target_obj(mp_event));
    }

    object &event::get_target_object()
    {
        return object::from_lv_object(lv_event_get_target_obj(mp_event));
    }

    uint32_t event::get_key()
    {
        return lv_event_get_key(mp_event);
    }

    lv_event_t *event::lv_event() const
    {
        return mp_event;
    }

    event::event(lv_event_t *lv_event) : mp_event(lv_event),
                                         mp_user_data(static_cast<event::descriptor *>(lv_event_get_user_data(lv_event))->m_user_data)
    {
    }
}
