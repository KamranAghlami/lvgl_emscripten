#include "io/filesystem.h"

#include <emscripten/fetch.h>

namespace io
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

        auto on_timeout = [](ui::lvgl::timer &timer)
        {
            auto &fs = io::filesystem::get();

            auto it = fs.m_cache.begin();

            while (it != fs.m_cache.end())
            {
                if (it->second->invalidated())
                {
                    delete it->second;

                    it = fs.m_cache.erase(it);
                }
                else
                    it++;
            }
        };

        mp_timer = std::make_unique<ui::lvgl::timer>(on_timeout, 10000);
    }

    filesystem::~filesystem()
    {
        for (auto &pair : m_cache)
            delete pair.second;
    }

    void filesystem::prefetch(const std::vector<std::string> &paths)
    {
        size_t count = paths.size() - std::count(paths.begin(), paths.end(), "");

        if (!count)
            return;

        m_prefetching_count += count;

        auto on_fetch = [this](const std::string &)
        {
            m_prefetching_count--;
        };

        for (const auto &path : paths)
            fetch(path, on_fetch);
    }

    void filesystem::fetch(const std::string &path, const fetch_callback &callback)
    {
        if (path.empty())
            return;

        std::string full_path = get_full_path(path);

        if (m_cache.find(full_path) != m_cache.end())
        {
            if (callback)
                callback(m_letter + std::string(":") + full_path);

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
            auto &fs = io::filesystem::get();
            auto path = static_cast<std::string *>(fetch->userData);

            fs.m_cache[*path] = new cache_entry(reinterpret_cast<const uint8_t *>(fetch->data), fetch->numBytes);

            auto range = fs.m_fetching_list.equal_range(*path);
            std::string lv_path = fs.m_letter + std::string(":") + *path;

            for (auto it = range.first; it != range.second; it++)
                if (it->second)
                    it->second(lv_path);

            fs.m_fetching_list.erase(*path);
            delete path;

            emscripten_fetch_close(fetch);
        };

        auto on_failed = [](emscripten_fetch_t *fetch)
        {
            LV_LOG_WARN("fetching %s failed, HTTP status code: %d.", fetch->url, fetch->status);

            auto &fs = io::filesystem::get();
            auto path = static_cast<std::string *>(fetch->userData);

            fs.m_fetching_list.erase(*path);
            delete path;

            emscripten_fetch_close(fetch);
        };

        emscripten_fetch_attr_t attribute;
        emscripten_fetch_attr_init(&attribute);

        strcpy(attribute.requestMethod, "GET");
        attribute.userData = new std::string(full_path);
        attribute.onsuccess = on_succeeded;
        attribute.onerror = on_failed;
        attribute.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;

        auto result = emscripten_fetch(&attribute, full_path.c_str());

        if (!result)
        {
            LV_LOG_WARN("fetching %s failed.", full_path.c_str());

            delete static_cast<std::string *>(attribute.userData);

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

        return new file_handle(iterator->first, iterator->second);
    }

    lv_fs_res_t filesystem::close(file_handle *file)
    {
        auto entry = m_cache[file->m_path];

        entry->decrease_reference();

        mp_timer->reset();

        delete file;

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

    std::string filesystem::get_full_path(const std::string &path)
    {
        if (path.empty())
            return "";

        auto is_prefix = [](const std::string &prefix, const std::string &string) -> bool
        {
            if (prefix.size() > string.size())
                return false;

            return string.substr(0, prefix.size()) == prefix;
        };

        const char *origin = emscripten_run_script_string("window.location.origin");

        std::string full_path;

        if (path[0] == '/')
            full_path = origin + path;
        else if (is_prefix("http://", path) || is_prefix("https://", path))
            full_path = path;
        else
        {
            const std::string _origin(origin);

            const char *path_name = emscripten_run_script_string("window.location.pathname");
            const char *last_slash = strrchr(path_name, '/');

            if (last_slash)
                full_path = _origin + std::string(path_name, last_slash + 1) + path;
            else
                full_path = _origin + path_name + '/' + path;
        }

        return full_path;
    }
}