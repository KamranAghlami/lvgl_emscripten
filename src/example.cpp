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

    ~example()
    {
        if (m_image)
            lv_obj_delete(m_image);
    }

private:
    void on_ready() override
    {
        auto on_fetch = [this](const std::string &path)
        {
            if (path.empty())
                return;

            m_image = lv_image_create(lv_screen_active());

            lv_image_set_src(m_image, path.c_str());
            lv_obj_center(m_image);
        };

        io::filesystem::get().fetch("img/lvgl.png", on_fetch);
    };

    lv_obj_t *m_image = nullptr;
};

DEFINE_MAIN(example);
