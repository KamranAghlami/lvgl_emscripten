#include "io/mouse.h"

namespace io
{
    mouse::mouse()
    {
        auto on_mouse_down = [](int type, const EmscriptenMouseEvent *mouse_event, void *user_data)
        {
            return static_cast<mouse *>(user_data)->on_mouse_down(type, mouse_event, user_data);
        };

        emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_FALSE, on_mouse_down);

        auto on_mouse_up = [](int type, const EmscriptenMouseEvent *mouse_event, void *user_data)
        {
            return static_cast<mouse *>(user_data)->on_mouse_up(type, mouse_event, user_data);
        };

        emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_FALSE, on_mouse_up);

        auto on_mouse_move = [](int type, const EmscriptenMouseEvent *mouse_event, void *user_data)
        {
            return static_cast<mouse *>(user_data)->on_mouse_move(type, mouse_event, user_data);
        };

        emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_FALSE, on_mouse_move);

        mp_device = lv_indev_create();

        auto on_mouse_read = [](lv_indev_t *device, lv_indev_data_t *data)
        {
            static_cast<mouse *>(lv_indev_get_driver_data(device))->on_mouse_read(data);
        };

        lv_indev_set_type(mp_device, LV_INDEV_TYPE_POINTER);
        lv_indev_set_read_cb(mp_device, on_mouse_read);
        lv_indev_set_mode(mp_device, LV_INDEV_MODE_EVENT);
        lv_indev_set_driver_data(mp_device, this);

        auto on_wheel = [](int type, const EmscriptenWheelEvent *wheel_event, void *user_data)
        {
            return static_cast<mouse *>(user_data)->on_wheel(type, wheel_event, user_data);
        };

        emscripten_set_wheel_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_FALSE, on_wheel);

        mp_device_aux = lv_indev_create();

        auto on_mouse_aux_read = [](lv_indev_t *device, lv_indev_data_t *data)
        {
            static_cast<mouse *>(lv_indev_get_driver_data(device))->on_mouse_aux_read(data);
        };

        lv_indev_set_type(mp_device_aux, LV_INDEV_TYPE_ENCODER);
        lv_indev_set_read_cb(mp_device_aux, on_mouse_aux_read);
        lv_indev_set_mode(mp_device_aux, LV_INDEV_MODE_EVENT);
        lv_indev_set_driver_data(mp_device_aux, this);
    }

    mouse::~mouse()
    {
        lv_indev_delete(mp_device_aux);
        lv_indev_delete(mp_device);
    }

    void mouse::set_scaling(float scaling)
    {
        m_scaling = scaling;
    }

    void mouse::set_group(lv_group_t *group)
    {
        lv_indev_set_group(mp_device_aux, group);
    }

    EM_BOOL mouse::on_mouse_down(int type, const EmscriptenMouseEvent *mouse_event, void *user_data)
    {
        switch (mouse_event->button)
        {
        case 0:
            m_last_state.x = mouse_event->targetX * m_scaling;
            m_last_state.y = mouse_event->targetY * m_scaling;
            m_last_state.pressed = true;

            lv_indev_read(mp_device);

            break;

        case 1:
            m_last_state.pressed_aux = true;

            lv_indev_read(mp_device_aux);

            break;

        default:
            break;
        }

        return EM_FALSE;
    }

    EM_BOOL mouse::on_mouse_up(int type, const EmscriptenMouseEvent *mouse_event, void *user_data)
    {
        switch (mouse_event->button)
        {
        case 0:
            m_last_state.x = mouse_event->targetX * m_scaling;
            m_last_state.y = mouse_event->targetY * m_scaling;
            m_last_state.pressed = false;

            lv_indev_read(mp_device);

            break;

        case 1:
            m_last_state.pressed_aux = false;

            lv_indev_read(mp_device_aux);

            break;

        default:
            break;
        }

        return EM_FALSE;
    }

    EM_BOOL mouse::on_mouse_move(int type, const EmscriptenMouseEvent *mouse_event, void *user_data)
    {
        m_last_state.x = mouse_event->targetX * m_scaling;
        m_last_state.y = mouse_event->targetY * m_scaling;

        lv_indev_read(mp_device);

        return EM_FALSE;
    }

    EM_BOOL mouse::on_wheel(int type, const EmscriptenWheelEvent *wheel_event, void *user_data)
    {
        if (wheel_event->deltaY)
        {
            m_last_state.offset += wheel_event->deltaY > 0 ? +1 : -1;

            lv_indev_read(mp_device_aux);
        }

        return EM_FALSE;
    }

    void mouse::on_mouse_read(lv_indev_data_t *data)
    {
        data->point.x = m_last_state.x;
        data->point.y = m_last_state.y;
        data->state = m_last_state.pressed ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
    }

    void mouse::on_mouse_aux_read(lv_indev_data_t *data)
    {
        data->enc_diff = m_last_state.offset;
        data->state = m_last_state.pressed_aux ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
        m_last_state.offset -= data->enc_diff;
    }
}
