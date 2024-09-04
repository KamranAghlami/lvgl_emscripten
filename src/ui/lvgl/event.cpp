#include "ui/lvgl/event.h"

#include <lvgl.h>

#include "ui/lvgl/object.h"

namespace ui
{
    namespace lvgl
    {
        event::code event::get_code()
        {
            return m_code;
        }

        event::key_code event::get_key_code()
        {
            return *static_cast<event::key_code *>(m_parameter);
        }

        uint32_t event::get_key_value()
        {
            return *static_cast<uint32_t *>(m_parameter);
        }

        void *event::user_data()
        {
            return m_user_data;
        }

        void *event::parameter()
        {
            return m_parameter;
        }

        object &event::current_target()
        {
            return *m_current_target;
        }

        object &event::original_target()
        {
            return *m_original_target;
        }

        event::event(void *lv_event)
        {
            auto e = static_cast<lv_event_t *>(lv_event);

            m_code = static_cast<event::code>(lv_event_get_code(e));

            auto dsc = static_cast<event::descriptor *>(lv_event_get_user_data(e));

            m_user_data = dsc->m_user_data;
            m_parameter = lv_event_get_param(e);

            lv_obj_t *lv_target_current = lv_event_get_current_target_obj(e);
            lv_obj_t *lv_target = lv_event_get_target_obj(e);

            const bool bubbled = lv_target_current != lv_target;

            m_current_target = &object::from_lv_object(lv_target_current);
            m_original_target = bubbled ? &object::from_lv_object(lv_target) : m_current_target;
        }
    }
}