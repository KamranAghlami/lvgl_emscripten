#pragma once

#include "ui/lvgl/group.h"

#define DEFINE_MAIN(class) \
    int main()             \
    {                      \
        static class app;  \
                           \
        return 0;          \
    }

class application
{
public:
    static application *get();

    application();
    virtual ~application();

    application(const application &) = delete;
    application(application &&) = delete;
    application &operator=(const application &) = delete;
    application &operator=(application &&) = delete;

    float scaling();

    void set_scaling(float scaling);
    void set_active_group(ui::lvgl::group &group);

protected:
    virtual void on_ready() = 0;

    float m_scaling = 1.0f;
};
