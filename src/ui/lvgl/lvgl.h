#pragma once

#include <functional>

#include "ui/lvgl/memory.h"
#include "ui/lvgl/event.h"
#include "ui/lvgl/group.h"
#include "ui/lvgl/timer.h"
#include "ui/lvgl/style.h"
#include "ui/lvgl/theme.h"
#include "ui/lvgl/object.h"
#include "ui/lvgl/screen.h"
#include "ui/lvgl/label.h"
#include "ui/lvgl/button.h"
#include "ui/lvgl/image.h"
#include "ui/lvgl/canvas.h"
#include "ui/lvgl/tabview.h"

namespace ui
{
    namespace lvgl
    {
        using async_callback = std::function<void(void *)>;

        void async_call(const async_callback &cb, void *user_data = nullptr);

        uint32_t random(const uint32_t min, uint32_t max);
    }
}