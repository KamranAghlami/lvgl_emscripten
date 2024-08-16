#pragma once

#include <lvgl.h>

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
    application();
    virtual ~application();

    application(const application &) = delete;
    application(application &&) = delete;
    application &operator=(const application &) = delete;
    application &operator=(application &&) = delete;

    void set_scaling(float scaling);
    void set_active_group(lv_group_t *group);

protected:
    virtual void update(float timestep) = 0;

private:
    float m_previous_timestamp = 0;
};
