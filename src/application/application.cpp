#include "application/application.h"

#include <assert.h>

#include <emscripten/html5.h>
#include <lvgl.h>

#include "driver/display.h"
#include "driver/filesystem.h"
#include "driver/touch.h"
#include "driver/mouse.h"
#include "driver/keyboard.h"

static application *s_instance = nullptr;

application *application::get()
{
    assert(s_instance);

    return s_instance;
}

application::application()
{
    assert(s_instance == nullptr);

    s_instance = this;

    lv_init();

    auto tick_get_cb = []() -> uint32_t
    {
        return emscripten_get_now();
    };

    lv_tick_set_cb(tick_get_cb);

    driver::display::get();
    driver::filesystem::get();
    driver::touch::get();
    driver::mouse::get();
    driver::keyboard::get();

    auto on_fs_ready = [](lv_timer_t *timer) -> void
    {
        auto *app = static_cast<application *>(lv_timer_get_user_data(timer));

        if (!driver::filesystem::get().ready())
            return;

        app->on_ready();

        lv_timer_delete(timer);
    };

    lv_timer_create(on_fs_ready, 0, this);

    auto on_update = [](double, void *) -> EM_BOOL
    {
        lv_timer_handler();

        return EM_TRUE;
    };

    emscripten_request_animation_frame_loop(on_update, nullptr);
}

application::~application()
{
    lv_deinit();
}

float application::scaling()
{
    return m_scaling;
}

float application::pixel_ratio()
{
    return emscripten_get_device_pixel_ratio();
}

void application::set_scaling(float scaling)
{
    m_scaling = scaling;

    scaling *= pixel_ratio();

    driver::display::get().set_scaling(scaling);
    driver::touch::get().set_scaling(scaling);
    driver::mouse::get().set_scaling(scaling);
}

void application::set_active_group(lv_group_t *group)
{
    driver::mouse::get().set_group(group);
    driver::keyboard::get().set_group(group);
}