#include "io/filesystem.h"

#include <iostream>
#include <emscripten/fetch.h>

namespace io
{
    filesystem::filesystem()
    {
        lv_fs_drv_init(&m_driver);

        m_driver.letter = 'N';
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

    void *filesystem::open(const char *path, lv_fs_mode_t mode)
    {
        printf("[filesystem::open] path: %s, mode: %d.\n", path, mode);

#if 0
        auto on_succeeded = [](emscripten_fetch_t *fetch)
        {
            printf("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);

            emscripten_fetch_close(fetch);
        };

        auto on_failed = [](emscripten_fetch_t *fetch)
        {
            printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);

            emscripten_fetch_close(fetch);
        };

        emscripten_fetch_attr_t attr;

        emscripten_fetch_attr_init(&attr);

        strcpy(attr.requestMethod, "GET");
        attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
        attr.onsuccess = on_succeeded;
        attr.onerror = on_failed;

        emscripten_fetch(&attr, path);
#else
        emscripten_fetch_attr_t attr;

        emscripten_fetch_attr_init(&attr);

        strcpy(attr.requestMethod, "GET");
        attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_SYNCHRONOUS;

        emscripten_fetch_t *fetch = emscripten_fetch(&attr, path);

        if (fetch)
        {
            if (fetch->status == 200)
                printf("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);
            else
                printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);

            emscripten_fetch_close(fetch);
        }
        else
            printf("Fetching %s failed.\n", path);
#endif

        return nullptr;
    }

    lv_fs_res_t filesystem::close(void *file)
    {
        printf("[filesystem::close] file: %p.\n", file);

        return LV_FS_RES_NOT_IMP;
    }

    lv_fs_res_t filesystem::read(void *file, void *buffer, uint32_t size, uint32_t *size_read)
    {
        printf("[filesystem::read] file: %p, buffer: %p, size: %u, size_read: %u.\n", file, buffer, size, *size_read);

        return LV_FS_RES_NOT_IMP;
    }

    lv_fs_res_t filesystem::seek(void *file, uint32_t position, lv_fs_whence_t whence)
    {
        printf("[filesystem::seek] file: %p, position: %u, whence: %d.\n", file, position, whence);

        return LV_FS_RES_NOT_IMP;
    }

    lv_fs_res_t filesystem::tell(void *file, uint32_t *position)
    {
        printf("[filesystem::tell] file: %p, position: %d.\n", file, *position);

        return LV_FS_RES_NOT_IMP;
    }
}