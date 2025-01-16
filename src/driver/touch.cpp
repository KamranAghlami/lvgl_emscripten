#include "driver/touch.h"

namespace driver
{
    touch::touch() : m_scaling(emscripten_get_device_pixel_ratio())
    {
        auto on_touch_start = [](int type, const EmscriptenTouchEvent *touch_event, void *user_data)
        {
            return static_cast<touch *>(user_data)->on_touch_start(type, touch_event, user_data);
        };

        emscripten_set_touchstart_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_TRUE, on_touch_start);

        auto on_touch_move = [](int type, const EmscriptenTouchEvent *touch_event, void *user_data)
        {
            return static_cast<touch *>(user_data)->on_touch_move(type, touch_event, user_data);
        };

        emscripten_set_touchmove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_TRUE, on_touch_move);

        auto on_touch_end = [](int type, const EmscriptenTouchEvent *touch_event, void *user_data)
        {
            return static_cast<touch *>(user_data)->on_touch_end(type, touch_event, user_data);
        };

        emscripten_set_touchend_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_TRUE, on_touch_end);

        auto on_touch_cancel = [](int type, const EmscriptenTouchEvent *touch_event, void *user_data)
        {
            return static_cast<touch *>(user_data)->on_touch_cancel(type, touch_event, user_data);
        };

        emscripten_set_touchcancel_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_TRUE, on_touch_cancel);
    }

    touch::~touch()
    {
        for (auto &dev : m_devices)
        {
            dev.second->~device();

            memory::free(dev.second);
        }
    }

    void touch::set_scaling(float scaling)
    {
        m_scaling = scaling;
    }

    EM_BOOL touch::on_touch_start(int type, const EmscriptenTouchEvent *touch_event, void *user_data)
    {
        for (size_t i = 0; i < touch_event->numTouches; i++)
        {
            const EmscriptenTouchPoint &touch_point = touch_event->touches[i];

            if (!touch_point.isChanged)
                continue;

            auto &dev = get_device(touch_point.identifier);

            dev.set_x(touch_point.targetX * m_scaling);
            dev.set_y(touch_point.targetY * m_scaling);
            dev.set_pressed(true);
            dev.read();
        }

        return EM_TRUE;
    }

    EM_BOOL touch::on_touch_move(int type, const EmscriptenTouchEvent *touch_event, void *user_data)
    {
        for (size_t i = 0; i < touch_event->numTouches; i++)
        {
            const EmscriptenTouchPoint &touch_point = touch_event->touches[i];

            if (!touch_point.isChanged)
                continue;

            auto &dev = get_device(touch_point.identifier);

            dev.set_x(touch_point.targetX * m_scaling);
            dev.set_y(touch_point.targetY * m_scaling);
            dev.set_pressed(true);
            dev.read();
        }

        return EM_TRUE;
    }

    EM_BOOL touch::on_touch_end(int type, const EmscriptenTouchEvent *touch_event, void *user_data)
    {
        for (size_t i = 0; i < touch_event->numTouches; i++)
        {
            const EmscriptenTouchPoint &touch_point = touch_event->touches[i];

            if (!touch_point.isChanged)
                continue;

            auto &dev = get_device(touch_point.identifier);

            dev.set_x(touch_point.targetX * m_scaling);
            dev.set_y(touch_point.targetY * m_scaling);
            dev.set_pressed(false);

            dev.read();

            release_device(dev);
        }

        return EM_TRUE;
    }

    EM_BOOL touch::on_touch_cancel(int type, const EmscriptenTouchEvent *touch_event, void *user_data)
    {
        for (size_t i = 0; i < touch_event->numTouches; i++)
        {
            const EmscriptenTouchPoint &touch_point = touch_event->touches[i];

            if (!touch_point.isChanged)
                continue;

            auto &dev = get_device(touch_point.identifier);

            dev.set_x(touch_point.targetX * m_scaling);
            dev.set_y(touch_point.targetY * m_scaling);
            dev.set_pressed(false);

            dev.read();

            release_device(dev);
        }

        return EM_TRUE;
    }

    touch::device &touch::get_device(int identifier)
    {
        const auto &dev = m_devices.find(identifier);

        if (dev != m_devices.end())
            return *dev->second;

        auto new_dev_mem = memory::allocate(sizeof(device));
        auto new_dev = new (new_dev_mem) device(identifier);
        auto p_dev = m_devices.emplace(identifier, new_dev).first->second;

        return *p_dev;
    }

    void touch::release_device(device &dev)
    {
        m_devices.erase(dev.get_identifier());

        dev.~device();

        memory::free(&dev);
    }

    touch::device::device(int identifier) : m_identifier(identifier), mp_indev(lv_indev_create())
    {
        auto on_touch_read = [](lv_indev_t *indev, lv_indev_data_t *data)
        {
            static_cast<device *>(lv_indev_get_driver_data(indev))->on_touch_read(data);
        };

        lv_indev_set_type(mp_indev, LV_INDEV_TYPE_POINTER);
        lv_indev_set_read_cb(mp_indev, on_touch_read);
        lv_indev_set_mode(mp_indev, LV_INDEV_MODE_EVENT);
        lv_indev_set_driver_data(mp_indev, this);
    }

    touch::device::~device()
    {
        auto delete_async = [](lv_timer_t *timer)
        {
            auto indev = static_cast<lv_indev_t *>(lv_timer_get_user_data(timer));

            if (lv_indev_get_active_obj() || lv_indev_get_scroll_obj(indev))
                return;

            lv_indev_delete(static_cast<lv_indev_t *>(lv_timer_get_user_data(timer)));
            lv_timer_delete(timer);
        };

        lv_timer_create(delete_async, 1000, mp_indev);
    }

    void touch::device::read()
    {
        lv_indev_read(mp_indev);
    }

    int touch::device::get_identifier()
    {
        return m_identifier;
    }

    void touch::device::set_x(const int x)
    {
        m_state.x = x;
    }

    void touch::device::set_y(const int y)
    {
        m_state.y = y;
    }

    void touch::device::set_pressed(const bool pressed)
    {
        m_state.pressed = pressed;
    }

    void touch::device::on_touch_read(lv_indev_data_t *data)
    {
        if (m_state.pressed)
        {
            data->point.x = m_state.x;
            data->point.y = m_state.y;
            data->state = LV_INDEV_STATE_PRESSED;
        }
        else
            data->state = LV_INDEV_STATE_RELEASED;
    }
}