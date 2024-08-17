#include "io/filesystem.h"

#include <emscripten/fetch.h>

namespace io
{
    filesystem::filesystem() : m_letter('N')
    {
        lv_fs_drv_init(&m_driver);

        m_driver.letter = m_letter;
        m_driver.cache_size = 0;

        m_driver.open_cb = [](lv_fs_drv_t *drive, const char *path, lv_fs_mode_t mode) -> void *
        {
            return static_cast<filesystem *>(drive->user_data)->open(path, mode);
        };

        m_driver.close_cb = [](lv_fs_drv_t *drive, void *file) -> lv_fs_res_t
        {
            return static_cast<filesystem *>(drive->user_data)->close(file);
        };

        m_driver.read_cb = [](lv_fs_drv_t *drive, void *file, void *buffer, uint32_t size, uint32_t *size_read) -> lv_fs_res_t
        {
            return static_cast<filesystem *>(drive->user_data)->read(file, buffer, size, size_read);
        };

        m_driver.seek_cb = [](lv_fs_drv_t *drive, void *file, uint32_t position, lv_fs_whence_t whence) -> lv_fs_res_t
        {
            return static_cast<filesystem *>(drive->user_data)->seek(file, position, whence);
        };

        m_driver.tell_cb = [](lv_fs_drv_t *drive, void *file, uint32_t *position) -> lv_fs_res_t
        {
            return static_cast<filesystem *>(drive->user_data)->tell(file, position);
        };

        m_driver.user_data = this;

        lv_fs_drv_register(&m_driver);
    }

    filesystem::~filesystem()
    {
    }

    void filesystem::fetch(const std::string &path, const fetch_callback callback)
    {
        if (path.empty())
            return;

        std::string full_path = get_full_path(path);

        emscripten_fetch_attr_t attribute;

        emscripten_fetch_attr_init(&attribute);

        strcpy(attribute.requestMethod, "GET");

        if (callback)
            attribute.userData = new fetch_context(full_path, callback);

        attribute.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;

        auto on_succeeded = [](emscripten_fetch_t *fetch)
        {
            auto context = static_cast<fetch_context *>(fetch->userData);

            LV_LOG_WARN("fetched %llu bytes from %s.", fetch->numBytes, fetch->url);

            auto &fs = io::filesystem::get();

            if (context->m_callback)
                context->m_callback(fs.m_letter + std::string(":") + context->m_path);

            delete context;

            emscripten_fetch_close(fetch);
        };

        auto on_failed = [](emscripten_fetch_t *fetch)
        {
            LV_LOG_WARN("fetching %s failed, HTTP status code: %d.", fetch->url, fetch->status);

            delete static_cast<fetch_context *>(fetch->userData);

            emscripten_fetch_close(fetch);
        };

        attribute.onsuccess = on_succeeded;
        attribute.onerror = on_failed;

        auto result = emscripten_fetch(&attribute, full_path.c_str());

        if (!result)
        {
            LV_LOG_WARN("fetching %s failed.", full_path.c_str());

            delete static_cast<fetch_context *>(attribute.userData);
        }
    }

    void *filesystem::open(const char *path, lv_fs_mode_t mode)
    {
        LV_LOG_WARN("path: %s, mode: %d.", path, mode);

        return nullptr;
    }

    lv_fs_res_t filesystem::close(void *file)
    {
        LV_LOG_WARN("file: %p.", file);

        return LV_FS_RES_NOT_IMP;
    }

    lv_fs_res_t filesystem::read(void *file, void *buffer, uint32_t size, uint32_t *size_read)
    {
        LV_LOG_WARN("file: %p, buffer: %p, size: %u, size_read: %u.", file, buffer, size, *size_read);

        return LV_FS_RES_NOT_IMP;
    }

    lv_fs_res_t filesystem::seek(void *file, uint32_t position, lv_fs_whence_t whence)
    {
        LV_LOG_WARN("file: %p, position: %u, whence: %d.", file, position, whence);

        return LV_FS_RES_NOT_IMP;
    }

    lv_fs_res_t filesystem::tell(void *file, uint32_t *position)
    {
        LV_LOG_WARN("file: %p, position: %d.", file, *position);

        return LV_FS_RES_NOT_IMP;
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
        else if (is_prefix(origin, path))
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