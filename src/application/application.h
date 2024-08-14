#pragma once

#include <cstdint>
#include <memory>

#define DEFINE_MAIN(application) \
    int main()                   \
    {                            \
        static application app;  \
        return 0;                \
    }

class application
{
public:
    application();
    virtual ~application() = default;

    application(const application &) = delete;
    application(application &&) = delete;
    application &operator=(const application &) = delete;
    application &operator=(application &&) = delete;

protected:
    virtual void update(float timestep) = 0;

private:
    float m_previous_timestamp = 0;
};
