#include <lvgl.h>

namespace ui
{
    namespace lvgl
    {
        void *malloc(size_t size)
        {
            return lv_malloc(size);
        }

        void free(void *data)
        {
            return lv_free(data);
        }
    }
}