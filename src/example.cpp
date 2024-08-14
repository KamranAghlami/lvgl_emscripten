#include "application/application.h"

#include <demos/lv_demos.h>

class example : public application
{
public:
    example()
    {
        lv_demo_widgets();
        lv_demo_widgets_start_slideshow();
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
