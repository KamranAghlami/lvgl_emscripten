#pragma once

#include <functional>

#include "ui/lvgl/event.h"
#include "ui/lvgl/group.h"
#include "ui/lvgl/timer.h"
#include "ui/lvgl/object.h"
#include "ui/lvgl/screen.h"

namespace ui
{
    namespace lvgl
    {
        using async_callback = std::function<void(void *)>;

        static void async_call(const async_callback &cb, void *user_data = nullptr);
    }
}