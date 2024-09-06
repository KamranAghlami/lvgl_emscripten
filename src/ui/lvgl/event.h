#pragma once

#include <functional>

extern "C"
{
    struct lv_event_t;
}

namespace ui
{
    namespace lvgl
    {
        class object;

        class event
        {
        public:
            using callback = std::function<void(event &)>;

            enum class code : uint32_t
            {
                ALL = 0,
                PRESSED,
                PRESSING,
                PRESS_LOST,
                SHORT_CLICKED,
                LONG_PRESSED,
                LONG_PRESSED_REPEAT,
                CLICKED,
                RELEASED,
                SCROLL_BEGIN,
                SCROLL_THROW_BEGIN,
                SCROLL_END,
                SCROLL,
                GESTURE,
                KEY,
                ROTARY,
                FOCUSED,
                DEFOCUSED,
                LEAVE,
                HIT_TEST,
                INDEV_RESET,
                HOVER_OVER,
                HOVER_LEAVE,
                COVER_CHECK,
                REFR_EXT_DRAW_SIZE,
                DRAW_MAIN_BEGIN,
                DRAW_MAIN,
                DRAW_MAIN_END,
                DRAW_POST_BEGIN,
                DRAW_POST,
                DRAW_POST_END,
                DRAW_TASK_ADDED,
                VALUE_CHANGED,
                INSERT,
                REFRESH,
                READY,
                CANCEL,
                CREATE,
                DELETE,
                CHILD_CHANGED,
                CHILD_CREATED,
                CHILD_DELETED,
                SCREEN_UNLOAD_START,
                SCREEN_LOAD_START,
                SCREEN_LOADED,
                SCREEN_UNLOADED,
                SIZE_CHANGED,
                STYLE_CHANGED,
                LAYOUT_CHANGED,
                GET_SELF_SIZE,
                INVALIDATE_AREA,
                RESOLUTION_CHANGED,
                COLOR_FORMAT_CHANGED,
                REFR_REQUEST,
                REFR_START,
                REFR_READY,
                RENDER_START,
                RENDER_READY,
                FLUSH_START,
                FLUSH_FINISH,
                FLUSH_WAIT_START,
                FLUSH_WAIT_FINISH,
                VSYNC,
                PREPROCESS = 0x8000,
            };

            struct descriptor
            {
                descriptor(const callback &cb, void *user_data = nullptr) : m_callback(cb), m_user_data(user_data) {}

                const callback m_callback;
                void *m_user_data;
                void *mp_descriptor;
            };

            code get_code();
            void *user_data();
            void *parameter();
            object &current_target_object();
            object &target_object();
            uint32_t get_key();

        private:
            event(lv_event_t *lv_event);

            lv_event_t *mp_event;
            void *mp_user_data;

            friend class object;
        };
    }
}
