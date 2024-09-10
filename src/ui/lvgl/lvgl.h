#pragma once

#include <functional>

#include "ui/lvgl/event.h"
#include "ui/lvgl/group.h"
#include "ui/lvgl/timer.h"
#include "ui/lvgl/object.h"
#include "ui/lvgl/screen.h"
#include "ui/lvgl/label.h"
#include "ui/lvgl/button.h"
#include "ui/lvgl/image.h"
#include "ui/lvgl/style.h"

namespace ui
{
    namespace lvgl
    {
        using async_callback = std::function<void(void *)>;

        void *malloc(size_t size);
        void free(void *data);

        void async_call(const async_callback &cb, void *user_data = nullptr);
    }
}