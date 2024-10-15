#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#include <lvgl.h>

#include "lvgl/memory.h"
#include "lvgl/timer.h"

namespace driver
{
    class filesystem
    {
    public:
        using fetch_callback = std::function<void(const lvgl::string &)>;

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

        void prefetch(const lvgl::vector<lvgl::string> &paths);
        void fetch(const lvgl::string &path, const fetch_callback &callback = nullptr);

        bool ready();

    private:
        class cache_entry
        {
        public:
            cache_entry(const uint8_t *data, const size_t size);

            void increase_reference();
            void decrease_reference();
            bool invalidated() const;

            const uint8_t *data() const;
            size_t size() const;

        private:
            lvgl::vector<uint8_t> m_data;
            size_t m_references = 0;
            float m_last_used = 0.0f;
        };

        struct file_handle
        {
            file_handle(const lvgl::string &path, const cache_entry *entry) : m_path(path),
                                                                              m_data(entry->data()),
                                                                              m_size(entry->size()),
                                                                              m_position(0) {}

            const lvgl::string m_path;
            const uint8_t *m_data;
            const size_t m_size;
            size_t m_position = 0;
        };

        filesystem();

        file_handle *open(const char *path, lv_fs_mode_t mode);
        lv_fs_res_t close(file_handle *file);
        lv_fs_res_t read(file_handle *file, void *buffer, uint32_t size, uint32_t *size_read);
        lv_fs_res_t seek(file_handle *file, uint32_t position, lv_fs_whence_t whence);
        lv_fs_res_t tell(file_handle *file, uint32_t *position);

        lvgl::string get_full_path(const lvgl::string &path);

        const char m_letter;
        size_t m_prefetching_count;
        lvgl::unordered_multimap<lvgl::string, fetch_callback> m_fetching_list;
        lvgl::unordered_map<lvgl::string, cache_entry *> m_cache;

        lv_fs_drv_t m_driver;
        lvgl::unique_ptr<lvgl::timer> mp_timer;
    };
}
