#include <lvgl.h>

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

    void memset(void *buffer, uint8_t value, size_t length)
    {
        return lv_memset(buffer, value, length);
    }
}
