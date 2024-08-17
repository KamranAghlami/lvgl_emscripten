#include "application/application.h"

#include <demos/lv_demos.h>

#include "io/filesystem.h"

class example : public application
{
public:
    example() : mp_group(lv_group_create())
    {
        set_active_group(mp_group);

        // lv_demo_widgets();

        auto image = lv_image_create(lv_scr_act());

        lv_obj_center(image);

        auto on_fetch = [this, image](const std::string &path)
        {
            lv_image_set_src(image, path.c_str());
        };

        io::filesystem::get().fetch("img/lvgl.png", on_fetch);
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
