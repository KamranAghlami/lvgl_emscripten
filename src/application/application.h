#pragma once

#include <cstdint>
#include <memory>
#include <lvgl.h>

#include "event/handler.h"
#include "event/window.h"

#define DEFINE_MAIN(class) \
    int main()             \
    {                      \
        static class app;  \
                           \
        return 0;          \
    }

class application : public event::handler<application>
{
public:
    application();
    virtual ~application();

    application(const application &) = delete;
    application(application &&) = delete;
    application &operator=(const application &) = delete;
    application &operator=(application &&) = delete;

protected:
    virtual void update(float timestep) = 0;

private:
    bool on_size_change(const event::window::size_changed &event);

    void update_size();
    void set_bitmap(const int x1, const int y1, const int x2, const int y2, uint8_t *buffer);

    float m_previous_timestamp = 0;

    double m_scaling = 1.0f;
    int m_width = 0;
    int m_height = 0;

    void *mp_draw_buf_1 = nullptr;
    void *mp_draw_buf_2 = nullptr;
    lv_display_t *mp_display = nullptr;
};
