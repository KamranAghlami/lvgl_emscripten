#pragma once

#include <functional>
#include <string>

#include <lvgl.h>

namespace io
{
    class filesystem
    {
    public:
        using fetch_callback = std::function<void(const std::string &)>;

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

        void fetch(const std::string &path, const fetch_callback callback = nullptr);

    private:
        struct fetch_context
        {
            fetch_context(const std::string &path, const fetch_callback callback) : m_path(path), m_callback(callback) {}

            const std::string m_path;
            const fetch_callback m_callback;
        };

        filesystem();

        void *open(const char *path, lv_fs_mode_t mode);
        lv_fs_res_t close(void *file);
        lv_fs_res_t read(void *file, void *buffer, uint32_t size, uint32_t *size_read);
        lv_fs_res_t seek(void *file, uint32_t position, lv_fs_whence_t whence);
        lv_fs_res_t tell(void *file, uint32_t *position);

        std::string get_full_path(const std::string &path);

        const char m_letter;

        lv_fs_drv_t m_driver;
    };
}
