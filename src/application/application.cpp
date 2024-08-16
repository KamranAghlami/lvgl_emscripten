#include "application/application.h"

#include <assert.h>

#include <emscripten/html5.h>

#include "io/display.h"
#include "io/touch.h"
#include "io/mouse.h"
#include "io/keyboard.h"

static application *s_instance = nullptr;

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
    io::touch::get();
    io::mouse::get();
    io::keyboard::get();

    auto on_update = [](double time, void *user_data) -> EM_BOOL
    {
        static const auto app = static_cast<application *>(user_data);

        float timestep = time - app->m_previous_timestamp;
        app->m_previous_timestamp = time;

        if (timestep < 0.0f)
            timestep = 0.0f;

        app->update(timestep);

        lv_timer_handler();

        return EM_TRUE;
    };

    emscripten_request_animation_frame_loop(on_update, this);
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

void application::set_active_group(lv_group_t *group)
{
    lv_group_set_default(group);

    io::mouse::get().set_group(group);
    io::keyboard::get().set_group(group);
}