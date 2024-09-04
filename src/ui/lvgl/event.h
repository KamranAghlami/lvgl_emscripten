#pragma once

#include <functional>

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

            enum class key_code : uint32_t
            {
                UP = 17,
                DOWN = 18,
                RIGHT = 19,
                LEFT = 20,
                ESC = 27,
                DEL = 127,
                BACKSPACE = 8,
                ENTER = 10,
                NEXT = 9,
                PREV = 11,
                HOME = 2,
                END = 3,
            };

            struct descriptor
            {
                descriptor(const callback &cb, void *user_data = nullptr) : m_callback(cb), m_user_data(user_data) {}

                const callback m_callback;
                void *m_user_data;
                void *mp_descriptor;
            };

            code get_code();
            key_code get_key_code();
            uint32_t get_key_value();
            void *user_data();
            void *parameter();
            object &current_target();
            object &original_target();

        private:
            event(void *lv_event);

            code m_code;
            void *m_user_data;
            void *m_parameter;
            object *m_current_target;
            object *m_original_target;

            friend class object;
        };
    }
}
