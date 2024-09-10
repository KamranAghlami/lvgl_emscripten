#include "ui/lvgl/lvgl.h"

#include <lvgl.h>

namespace ui
{
    namespace lvgl
    {
        class async_info
        {
        public:
            async_info(const async_callback &cb, void *user_data) : m_callback(cb), m_user_data(user_data) {};

            void operator()() { m_callback(m_user_data); }

        private:
            async_callback m_callback;
            void *m_user_data;
        };

        void *malloc(size_t size)
        {
            return lv_malloc(size);
        }

        void free(void *data)
        {
            return lv_free(data);
        }

        void async_call(const async_callback &cb, void *user_data)
        {
            auto async_cb = [](void *user_data)
            {
                auto info = static_cast<async_info *>(user_data);

                (*info)();

                info->~async_info();

                lv_free(info);
            };

            auto info_mem = lv_malloc(sizeof(async_info));
            auto info = new (info_mem) async_info(cb, user_data);

            lv_async_call(async_cb, info);
        }
    }
}