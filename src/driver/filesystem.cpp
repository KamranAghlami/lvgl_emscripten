#include "driver/filesystem.h"

#include <emscripten/emscripten.h>
#include <emscripten/fetch.h>

namespace driver
{
    filesystem::filesystem() : m_letter('N'), m_prefetching_count(0)
    {
        lv_fs_drv_init(&m_driver);

        m_driver.letter = m_letter;
        m_driver.cache_size = 4U * 1024U;

        m_driver.ready_cb = [](lv_fs_drv_t *drive) -> bool
        {
            return static_cast<filesystem *>(drive->user_data)->ready();
        };

        m_driver.open_cb = [](lv_fs_drv_t *drive, const char *path, lv_fs_mode_t mode) -> void *
        {
            return static_cast<filesystem *>(drive->user_data)->open(path, mode);
        };

        m_driver.close_cb = [](lv_fs_drv_t *drive, void *file) -> lv_fs_res_t
        {
            return static_cast<filesystem *>(drive->user_data)->close(static_cast<file_handle *>(file));
        };

        m_driver.read_cb = [](lv_fs_drv_t *drive, void *file, void *buffer, uint32_t size, uint32_t *size_read) -> lv_fs_res_t
        {
            return static_cast<filesystem *>(drive->user_data)->read(static_cast<file_handle *>(file), buffer, size, size_read);
        };

        m_driver.seek_cb = [](lv_fs_drv_t *drive, void *file, uint32_t position, lv_fs_whence_t whence) -> lv_fs_res_t
        {
            return static_cast<filesystem *>(drive->user_data)->seek(static_cast<file_handle *>(file), position, whence);
        };

        m_driver.tell_cb = [](lv_fs_drv_t *drive, void *file, uint32_t *position) -> lv_fs_res_t
        {
            return static_cast<filesystem *>(drive->user_data)->tell(static_cast<file_handle *>(file), position);
        };

        m_driver.user_data = this;

        lv_fs_drv_register(&m_driver);

        auto on_timeout = [](lv_timer_t *timer)
        {
            auto &fs = driver::filesystem::get();

            auto it = fs.m_cache.begin();

            while (it != fs.m_cache.end())
            {
                if (it->second->invalidated())
                {
                    std::destroy_at(it->second);

                    memory::free(it->second);

                    it = fs.m_cache.erase(it);
                }
                else
                    it++;
            }
        };

        mp_timer = lv_timer_create(on_timeout, 10000, nullptr);
    }

    filesystem::~filesystem()
    {
        lv_timer_delete(mp_timer);

        for (auto &pair : m_cache)
        {
            std::destroy_at(pair.second);

            memory::free(pair.second);
        }
    }

    void filesystem::prefetch(const memory::vector<memory::string> &paths)
    {
        size_t count = paths.size() - std::count(paths.begin(), paths.end(), "");

        if (!count)
            return;

        m_prefetching_count += count;

        auto on_fetch = [this](const memory::string &)
        {
            m_prefetching_count--;
        };

        for (const auto &path : paths)
            fetch(path, on_fetch);
    }

    void filesystem::fetch(const memory::string &path, const fetch_callback &callback)
    {
        if (path.empty())
            return;

        memory::string full_path = get_full_path(path);

        if (m_cache.find(full_path) != m_cache.end())
        {
            if (callback)
                callback(m_letter + memory::string(":") + full_path);

            return;
        }

        auto fetching_range = m_fetching_list.equal_range(full_path);

        if (fetching_range.first != fetching_range.second)
        {
            m_fetching_list.emplace(full_path, callback);

            return;
        }

        auto on_succeeded = [](emscripten_fetch_t *fetch)
        {
            auto &fs = driver::filesystem::get();
            auto path = static_cast<memory::string *>(fetch->userData);

            auto cache_mem = memory::allocate(sizeof(cache_entry));
            auto cache = new (cache_mem) cache_entry(reinterpret_cast<const uint8_t *>(fetch->data), fetch->numBytes);

            fs.m_cache[*path] = cache;

            auto range = fs.m_fetching_list.equal_range(*path);
            memory::string lv_path = fs.m_letter + memory::string(":") + *path;

            for (auto it = range.first; it != range.second; it++)
                if (it->second)
                    it->second(lv_path);

            fs.m_fetching_list.erase(*path);

            std::destroy_at(path);

            memory::free(path);

            emscripten_fetch_close(fetch);
        };

        auto on_failed = [](emscripten_fetch_t *fetch)
        {
            LV_LOG_WARN("fetching %s failed, HTTP status code: %d.", fetch->url, fetch->status);

            auto &fs = driver::filesystem::get();
            auto path = static_cast<memory::string *>(fetch->userData);

            fs.m_fetching_list.erase(*path);

            std::destroy_at(path);

            memory::free(path);

            emscripten_fetch_close(fetch);
        };

        emscripten_fetch_attr_t attribute;
        emscripten_fetch_attr_init(&attribute);

        auto user_data_mem = memory::allocate(sizeof(memory::string));
        auto user_data = new (user_data_mem) memory::string(full_path);

        strcpy(attribute.requestMethod, "GET");
        attribute.userData = user_data;
        attribute.onsuccess = on_succeeded;
        attribute.onerror = on_failed;
        attribute.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;

        auto result = emscripten_fetch(&attribute, full_path.c_str());

        if (!result)
        {
            LV_LOG_WARN("fetching %s failed.", full_path.c_str());

            auto _path = static_cast<memory::string *>(attribute.userData);

            std::destroy_at(_path);

            memory::free(_path);

            return;
        }

        m_fetching_list.emplace(full_path, callback);
    }

    bool filesystem::ready()
    {
        return !m_prefetching_count;
    }

    filesystem::cache_entry::cache_entry(const uint8_t *data, const size_t size) : m_data(data, data + size)
    {
    }

    void filesystem::cache_entry::increase_reference()
    {
        m_references++;
    }

    void filesystem::cache_entry::decrease_reference()
    {
        m_references--;

        if (!m_references)
            m_last_used = emscripten_get_now();
    }

    bool filesystem::cache_entry::invalidated() const
    {
        if (m_last_used == 0.0f)
            return false;

        return !m_references && (emscripten_get_now() - m_last_used > 10000.f);
    }

    const uint8_t *filesystem::cache_entry::data() const
    {
        return m_data.data();
    }

    size_t filesystem::cache_entry::size() const
    {
        return m_data.size();
    }

    filesystem::file_handle *filesystem::open(const char *path, lv_fs_mode_t mode)
    {
        if (mode & LV_FS_MODE_WR)
            return nullptr;

        auto iterator = m_cache.find(path);

        if (iterator == m_cache.end())
            return nullptr;

        iterator->second->increase_reference();

        auto handle_mem = memory::allocate(sizeof(file_handle));
        auto handle = new (handle_mem) file_handle(iterator->first, iterator->second);

        return handle;
    }

    lv_fs_res_t filesystem::close(file_handle *file)
    {
        auto entry = m_cache[file->m_path];

        entry->decrease_reference();

        lv_timer_reset(mp_timer);

        std::destroy_at(file);

        memory::free(file);

        return LV_FS_RES_OK;
    }

    lv_fs_res_t filesystem::read(file_handle *file, void *buffer, uint32_t size, uint32_t *size_read)
    {
        size_t availble = file->m_size - file->m_position;
        size_t read_size = std::min(static_cast<size_t>(size), availble);

        memcpy(buffer, reinterpret_cast<const void *>(file->m_data + file->m_position), read_size);

        file->m_position += read_size;
        *size_read = read_size;

        return LV_FS_RES_OK;
    }

    lv_fs_res_t filesystem::seek(file_handle *file, uint32_t position, lv_fs_whence_t whence)
    {
        switch (whence)
        {
        case LV_FS_SEEK_SET:
            file->m_position = position;
            break;

        case LV_FS_SEEK_CUR:
            file->m_position += position;
            break;

        case LV_FS_SEEK_END:
            file->m_position = file->m_size - position;
            break;
        }

        return LV_FS_RES_OK;
    }

    lv_fs_res_t filesystem::tell(file_handle *file, uint32_t *position)
    {
        *position = file->m_position;

        return LV_FS_RES_OK;
    }

    memory::string filesystem::get_full_path(const memory::string &path)
    {
        const memory::string script = "new URL('" + path + "', window.location.href).href";

        return emscripten_run_script_string(script.c_str());
    }
}