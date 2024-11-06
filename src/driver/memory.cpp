#include "driver/memory.h"

#include <lvgl.h>

namespace driver
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
