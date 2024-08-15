#include "application/application.h"

#include <demos/lv_demos.h>

class example : public application
{
public:
    example()
    {
        lv_demo_widgets();
    }

    ~example()
    {
    }

private:
    void update(float timestep) override
    {
    }
};

DEFINE_MAIN(example);
