#include "application/application.h"

#include "io/filesystem.h"

class example : public application
{
public:
    example()
    {
        io::filesystem::get().prefetch({
            "img/lvgl.png",
        });
    }

private:
    void on_ready() override
    {
        auto image = lv_image_create(lv_scr_act());
        auto on_fetch = [image](const std::string &path)
        {
            if (!path.empty())
                lv_image_set_src(image, path.c_str());

            lv_obj_center(image);
        };

        io::filesystem::get().fetch("img/lvgl.png", on_fetch);
    };
};

DEFINE_MAIN(example);
