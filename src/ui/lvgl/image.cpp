#include "ui/lvgl/image.h"

#include <lvgl.h>

namespace ui
{
    namespace lvgl
    {
        image::image(object &parent) : object(lv_image_create(parent.lv_object()))
        {
        }

        image::~image()
        {
        }
    }
}
