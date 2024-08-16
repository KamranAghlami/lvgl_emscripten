#include "input/touch.h"

namespace input
{
    touch::touch()
    {
        auto on_touch_start = [](int type, const EmscriptenTouchEvent *touch_event, void *user_data)
        {
            return static_cast<touch *>(user_data)->on_touch_start(type, touch_event, user_data);
        };

        emscripten_set_touchstart_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_FALSE, on_touch_start);

        auto on_touch_move = [](int type, const EmscriptenTouchEvent *touch_event, void *user_data)
        {
            return static_cast<touch *>(user_data)->on_touch_move(type, touch_event, user_data);
        };

        emscripten_set_touchmove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_FALSE, on_touch_move);

        auto on_touch_end = [](int type, const EmscriptenTouchEvent *touch_event, void *user_data)
        {
            return static_cast<touch *>(user_data)->on_touch_end(type, touch_event, user_data);
        };

        emscripten_set_touchend_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_FALSE, on_touch_end);

        auto on_touch_cancel = [](int type, const EmscriptenTouchEvent *touch_event, void *user_data)
        {
            return static_cast<touch *>(user_data)->on_touch_cancel(type, touch_event, user_data);
        };

        emscripten_set_touchcancel_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_FALSE, on_touch_cancel);

        mp_device = lv_indev_create();

        auto on_touch_read = [](lv_indev_t *device, lv_indev_data_t *data)
        {
            static_cast<touch *>(lv_indev_get_driver_data(device))->on_touch_read(data);
        };

        lv_indev_set_type(mp_device, LV_INDEV_TYPE_POINTER);
        lv_indev_set_read_cb(mp_device, on_touch_read);
        lv_indev_set_mode(mp_device, LV_INDEV_MODE_EVENT);
        lv_indev_set_driver_data(mp_device, this);
    }

    touch::~touch()
    {
        lv_indev_delete(mp_device);
    }

    void touch::set_scaling(float scaling)
    {
        m_scaling = scaling;
    }

    EM_BOOL touch::on_touch_start(int type, const EmscriptenTouchEvent *touch_event, void *user_data)
    {
        if (!touch_event->numTouches)
            return EM_FALSE;

        const EmscriptenTouchPoint &touch_point = touch_event->touches[0];

        if (!touch_point.isChanged)
            return EM_FALSE;

        m_last_state.x = touch_point.targetX * m_scaling;
        m_last_state.y = touch_point.targetY * m_scaling;
        m_last_state.present = true;

        lv_indev_read(mp_device);

        return EM_FALSE;
    }

    EM_BOOL touch::on_touch_move(int type, const EmscriptenTouchEvent *touch_event, void *user_data)
    {
        if (!touch_event->numTouches)
            return EM_FALSE;

        const EmscriptenTouchPoint &touch_point = touch_event->touches[0];

        if (!touch_point.isChanged)
            return EM_FALSE;

        m_last_state.x = touch_point.targetX * m_scaling;
        m_last_state.y = touch_point.targetY * m_scaling;
        m_last_state.present = true;

        lv_indev_read(mp_device);

        return EM_FALSE;
    }

    EM_BOOL touch::on_touch_end(int type, const EmscriptenTouchEvent *touch_event, void *user_data)
    {
        if (!touch_event->numTouches)
            return EM_FALSE;

        const EmscriptenTouchPoint &touch_point = touch_event->touches[0];

        if (!touch_point.isChanged)
            return EM_FALSE;

        m_last_state.x = touch_point.targetX * m_scaling;
        m_last_state.y = touch_point.targetY * m_scaling;
        m_last_state.present = false;

        lv_indev_read(mp_device);

        return EM_FALSE;
    }

    EM_BOOL touch::on_touch_cancel(int type, const EmscriptenTouchEvent *touch_event, void *user_data)
    {
        if (!touch_event->numTouches)
            return EM_FALSE;

        const EmscriptenTouchPoint &touch_point = touch_event->touches[0];

        if (!touch_point.isChanged)
            return EM_FALSE;

        m_last_state.present = false;

        lv_indev_read(mp_device);

        return EM_FALSE;
    }

    void touch::on_touch_read(lv_indev_data_t *data)
    {
        if (m_last_state.present)
        {
            data->point.x = m_last_state.x;
            data->point.y = m_last_state.y;
            data->state = LV_INDEV_STATE_PRESSED;
        }
        else
            data->state = LV_INDEV_STATE_RELEASED;
    }
}