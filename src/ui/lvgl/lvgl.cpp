#include "ui/lvgl/lvgl.h"

#include <lvgl.h>

namespace ui
{
    namespace lvgl
    {
        struct async_info
        {
            async_callback callback;
            void *user_data;
        };

        void async_call(const async_callback &cb, void *user_data)
        {
            auto async_cb = [](void *user_data)
            {
                auto info = static_cast<async_info *>(user_data);

                info->callback(info->user_data);

                lv_free(info);
            };

            auto info = static_cast<async_info *>(lv_malloc(sizeof(async_info)));

            info->callback = cb;
            info->user_data = user_data;

            lv_async_call(async_cb, info);
        }
    }
}