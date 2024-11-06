#pragma once

#include <functional>

#include "lvgl/event.h"
#include "lvgl/group.h"
#include "lvgl/timer.h"
#include "lvgl/style.h"
#include "lvgl/theme.h"
#include "lvgl/object.h"
#include "lvgl/screen.h"
#include "lvgl/label.h"
#include "lvgl/button.h"
#include "lvgl/image.h"
#include "lvgl/canvas.h"
#include "lvgl/tabview.h"
#include "lvgl/table.h"
#include "lvgl/text_area.h"

namespace lvgl
{
    using async_callback = std::function<void(void *)>;

    void async_call(const async_callback &cb, void *user_data = nullptr);

    uint32_t random(const uint32_t min, uint32_t max);
}
