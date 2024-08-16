#pragma once

#include <lvgl.h>

namespace io
{
    class filesystem
    {
    public:
        static filesystem &get()
        {
            static filesystem instance;

            return instance;
        };

        ~filesystem();

        filesystem(const filesystem &) = delete;
        filesystem(filesystem &&) = delete;
        filesystem &operator=(const filesystem &) = delete;
        filesystem &operator=(filesystem &&) = delete;

    private:
        filesystem();

        void *open(const char *path, lv_fs_mode_t mode);
        lv_fs_res_t close(void *file);
        lv_fs_res_t read(void *file, void *buffer, uint32_t size, uint32_t *size_read);
        lv_fs_res_t seek(void *file, uint32_t position, lv_fs_whence_t whence);
        lv_fs_res_t tell(void *file, uint32_t *position);

        lv_fs_drv_t m_driver;
    };
}
