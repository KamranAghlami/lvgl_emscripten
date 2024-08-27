#pragma once

#include <cinttypes>
#include <unordered_map>
#include <functional>
#include <vector>

namespace ui
{
    namespace lvgl
    {
        class object
        {
        public:
            enum class flag : uint32_t
            {
                HIDDEN = (1L << 0),
                CLICKABLE = (1L << 1),
                CLICK_FOCUSABLE = (1L << 2),
                CHECKABLE = (1L << 3),
                SCROLLABLE = (1L << 4),
                SCROLL_ELASTIC = (1L << 5),
                SCROLL_MOMENTUM = (1L << 6),
                SCROLL_ONE = (1L << 7),
                SCROLL_CHAIN_HOR = (1L << 8),
                SCROLL_CHAIN_VER = (1L << 9),
                SCROLL_CHAIN = (SCROLL_CHAIN_HOR | SCROLL_CHAIN_VER),
                SCROLL_ON_FOCUS = (1L << 10),
                SCROLL_WITH_ARROW = (1L << 11),
                SNAPPABLE = (1L << 12),
                PRESS_LOCK = (1L << 13),
                EVENT_BUBBLE = (1L << 14),
                GESTURE_BUBBLE = (1L << 15),
                ADV_HITTEST = (1L << 16),
                IGNORE_LAYOUT = (1L << 17),
                FLOATING = (1L << 18),
                SEND_DRAW_TASK_EVENTS = (1L << 19),
                OVERFLOW_VISIBLE = (1L << 20),
                FLEX_IN_NEW_TRACK = (1L << 21),
                LAYOUT_1 = (1L << 23),
                LAYOUT_2 = (1L << 24),
                WIDGET_1 = (1L << 25),
                WIDGET_2 = (1L << 26),
                USER_1 = (1L << 27),
                USER_2 = (1L << 28),
                USER_3 = (1L << 29),
                USER_4 = (1L << 30),
            };

            enum class state : uint16_t
            {
                DEFAULT = 0x0000,
                CHECKED = 0x0001,
                FOCUSED = 0x0002,
                FOCUS_KEY = 0x0004,
                EDITED = 0x0008,
                HOVERED = 0x0010,
                PRESSED = 0x0020,
                SCROLLED = 0x0040,
                DISABLED = 0x0080,
                USER_1 = 0x1000,
                USER_2 = 0x2000,
                USER_3 = 0x4000,
                USER_4 = 0x8000,
                ANY = 0xFFFF,
            };

            enum class alignment : uint8_t
            {
                DEFAULT = 0,
                TOP_LEFT,
                TOP_MID,
                TOP_RIGHT,
                BOTTOM_LEFT,
                BOTTOM_MID,
                BOTTOM_RIGHT,
                LEFT_MID,
                RIGHT_MID,
                CENTER,
                OUT_TOP_LEFT,
                OUT_TOP_MID,
                OUT_TOP_RIGHT,
                OUT_BOTTOM_LEFT,
                OUT_BOTTOM_MID,
                OUT_BOTTOM_RIGHT,
                OUT_LEFT_TOP,
                OUT_LEFT_MID,
                OUT_LEFT_BOTTOM,
                OUT_RIGHT_TOP,
                OUT_RIGHT_MID,
                OUT_RIGHT_BOTTOM,
            };

            struct event
            {
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
                    LAST,
                    PREPROCESS = 0x8000,
                };

                struct descriptor
                {
                    descriptor(const callback &cb) : m_callback(cb) {}

                    const callback m_callback;
                    void *mp_descriptor;
                };

                code m_code;
                object &m_current_target;
                object &m_original_target;
            };

            object(object *parent);

            virtual ~object();

            object(const object &) = delete;
            object(object &&) = delete;
            object &operator=(const object &) = delete;
            object &operator=(object &&) = delete;

            object &add_flag(const flag f);
            object &remove_flag(const flag f);
            bool has_flag(const flag f);
            object &add_state(const state s);
            object &remove_state(const state s);
            bool has_state(const state s);

            object &set_x(const int32_t x);
            object &set_y(const int32_t y);
            object &set_pos(const int32_t x, const int32_t y);
            object &set_width(const int32_t width);
            object &set_height(const int32_t height);
            object &set_size(const int32_t width, const int32_t height);

            int32_t x();
            int32_t y();
            int32_t width();
            int32_t height();

            object &align(const alignment align, const int32_t x_ofs = 0, const int32_t y_ofs = 0);
            object &align_to(const object &base, const alignment align, const int32_t x_ofs = 0, const int32_t y_ofs = 0);

            object &invalidate();

            bool is_visible();

            void add_event_callback(event::code code, const event::callback &callback);

            void *lv_object();

        protected:
            static object &from_lv_object(void *lv_obj);

            explicit object(void *lv_obj);

        private:
            static std::unordered_map<void *, object *> s_objects;

            void *mp_object;

            std::vector<event::descriptor *> m_event_descriptors;
        };

        inline object::flag operator|(object::flag lhs, object::flag rhs)
        {
            return static_cast<object::flag>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
        }

        inline object::flag operator&(object::flag lhs, object::flag rhs)
        {
            return static_cast<object::flag>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
        }

        inline object::flag operator^(object::flag lhs, object::flag rhs)
        {
            return static_cast<object::flag>(static_cast<uint32_t>(lhs) ^ static_cast<uint32_t>(rhs));
        }

        inline object::flag operator~(object::flag lhs)
        {
            return static_cast<object::flag>(~static_cast<uint32_t>(lhs));
        }

        inline object::flag &operator|=(object::flag &lhs, object::flag rhs)
        {
            lhs = lhs | rhs;

            return lhs;
        }

        inline object::flag &operator&=(object::flag &lhs, object::flag rhs)
        {
            lhs = lhs & rhs;

            return lhs;
        }

        inline object::flag &operator^=(object::flag &lhs, object::flag rhs)
        {
            lhs = lhs ^ rhs;

            return lhs;
        }

        inline object::state operator|(object::state lhs, object::state rhs)
        {
            return static_cast<object::state>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
        }

        inline object::state operator&(object::state lhs, object::state rhs)
        {
            return static_cast<object::state>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
        }

        inline object::state operator^(object::state lhs, object::state rhs)
        {
            return static_cast<object::state>(static_cast<uint32_t>(lhs) ^ static_cast<uint32_t>(rhs));
        }

        inline object::state operator~(object::state lhs)
        {
            return static_cast<object::state>(~static_cast<uint32_t>(lhs));
        }

        inline object::state &operator|=(object::state &lhs, object::state rhs)
        {
            lhs = lhs | rhs;

            return lhs;
        }

        inline object::state &operator&=(object::state &lhs, object::state rhs)
        {
            lhs = lhs & rhs;

            return lhs;
        }

        inline object::state &operator^=(object::state &lhs, object::state rhs)
        {
            lhs = lhs ^ rhs;

            return lhs;
        }
    }
}