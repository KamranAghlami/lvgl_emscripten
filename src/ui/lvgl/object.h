#pragma once

#include <cinttypes>
#include <unordered_map>
#include <functional>
#include <vector>

namespace ui
{
    namespace lvgl
    {
        class screen;

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

            enum class layout : uint8_t
            {
                NONE,
                FLEX,
                GRID,
            };

            enum class flex_flow : uint8_t
            {
                ROW = 0x00,
                COLUMN = 0x01,
                ROW_WRAP = ROW | 0x04,
                ROW_REVERSE = ROW | 0x08,
                ROW_WRAP_REVERSE = ROW | 0x04 | 0x08,
                COLUMN_WRAP = COLUMN | 0x04,
                COLUMN_REVERSE = COLUMN | 0x08,
                COLUMN_WRAP_REVERSE = COLUMN | 0x04 | 0x08,
            };

            enum class flex_alignment : uint8_t
            {
                START,
                END,
                CENTER,
                SPACE_EVENLY,
                SPACE_AROUND,
                SPACE_BETWEEN,
            };

            enum class grid_alignment : uint8_t
            {
                START,
                CENTER,
                END,
                STRETCH,
                SPACE_EVENLY,
                SPACE_AROUND,
                SPACE_BETWEEN,
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
                    PREPROCESS = 0x8000,
                };

                struct descriptor
                {
                    descriptor(const callback &cb, void *user_data = nullptr) : m_callback(cb), m_user_data(user_data) {}

                    const callback m_callback;
                    void *m_user_data;
                    void *mp_descriptor;
                };

                code m_code;
                void *m_user_data;
                void *m_parameter;
                object &m_current_target;
                object &m_original_target;
            };

            static int32_t SIZE_CONTENT();
            static int32_t PERCENTAGE(uint32_t percentage);
            static int32_t GRID_CONTENT();
            static int32_t GRID_FR(uint32_t fr);
            static int32_t GRID_TEMPLATE_LAST();

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

            object &set_layout(layout l);
            object &update_layout();
            object &set_flex_flow(flex_flow f);
            object &set_flex_align(flex_alignment main, flex_alignment cross = flex_alignment::START, flex_alignment track_cross = flex_alignment::START);
            object &set_flex_grow(uint8_t grow);
            object &set_grid_dsc_array(const int32_t col_dsc[], const int32_t row_dsc[]);
            object &set_grid_align(grid_alignment column, grid_alignment row);
            object &set_grid_cell(grid_alignment column, int32_t col_pos, int32_t col_span,
                                  grid_alignment row, int32_t row_pos, int32_t row_span);

            object &invalidate();

            bool is_visible();

            void add_event_callback(event::code c, const event::callback &callback, void *user_data = nullptr);
            void send_event(event::code c, void *parameter = nullptr);

            int32_t index();
            void set_index(int32_t index);

            object *parent();
            void set_parent(object &parent);

            object *child(int32_t index = 0);
            uint32_t child_count();

            object *sibling(int32_t index = 1);

            screen &screen();

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