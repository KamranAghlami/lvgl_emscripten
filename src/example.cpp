#include "application/application.h"

#include <demos/lv_demos.h>

class example : public application
{
public:
    example() : mp_group(lv_group_create())
    {
        set_active_group(mp_group);

        lv_demo_widgets();
    }

    ~example()
    {
        lv_group_delete(mp_group);
    }

private:
    void update(float timestep) override
    {
    }

    lv_group_t *mp_group = nullptr;
};

DEFINE_MAIN(example);
