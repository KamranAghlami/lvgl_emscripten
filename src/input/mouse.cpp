#include "input/mouse.h"

namespace input
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
    }

    mouse::~mouse()
    {
        lv_indev_delete(mp_device);
    }

    EM_BOOL mouse::on_mouse_down(int type, const EmscriptenMouseEvent *mouse_event, void *user_data)
    {
        m_last_state.x = mouse_event->targetX;
        m_last_state.y = mouse_event->targetY;
        m_last_state.pressed = true;

        lv_indev_read(mp_device);

        return EM_FALSE;
    }

    EM_BOOL mouse::on_mouse_up(int type, const EmscriptenMouseEvent *mouse_event, void *user_data)
    {
        m_last_state.pressed = false;

        lv_indev_read(mp_device);

        return EM_FALSE;
    }

    EM_BOOL mouse::on_mouse_move(int type, const EmscriptenMouseEvent *mouse_event, void *user_data)
    {
        if (!m_last_state.pressed)
            return EM_FALSE;

        m_last_state.x = mouse_event->targetX;
        m_last_state.y = mouse_event->targetY;

        lv_indev_read(mp_device);

        return EM_FALSE;
    }

    void mouse::on_mouse_read(lv_indev_data_t *data)
    {
        if (m_last_state.pressed)
        {
            data->point.x = m_last_state.x;
            data->point.y = m_last_state.y;
            data->state = LV_INDEV_STATE_PRESSED;
        }
        else
            data->state = LV_INDEV_STATE_RELEASED;
    }
}
