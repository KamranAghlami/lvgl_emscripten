#include "application/application.h"

#include <assert.h>

#include <emscripten/html5.h>
#include <lvgl.h>

#include "io/display.h"
#include "io/filesystem.h"
#include "io/touch.h"
#include "io/mouse.h"
#include "io/keyboard.h"

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

    io::display::get();
    io::filesystem::get();
    io::touch::get();
    io::mouse::get();
    io::keyboard::get();

    set_scaling(emscripten_get_device_pixel_ratio());

    auto on_fs_ready = [](lv_timer_t *timer) -> void
    {
        auto *app = static_cast<application *>(lv_timer_get_user_data(timer));

        if (!io::filesystem::get().ready())
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

void application::set_scaling(float scaling)
{
    io::display::get().set_scaling(scaling);
    io::touch::get().set_scaling(scaling);
    io::mouse::get().set_scaling(scaling);
}

void application::set_active_group(ui::lvgl::group &group)
{
    io::mouse::get().set_group(group);
    io::keyboard::get().set_group(group);
}