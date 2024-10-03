#pragma once

#include <cinttypes>
#include <unordered_map>
#include <vector>

#include "ui/lvgl/memory.h"
#include "ui/lvgl/event.h"
#include "ui/lvgl/group.h"

extern "C"
{
    struct lv_obj_t;
}

namespace ui
{
    namespace lvgl
    {
        class screen;
        class style;

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

            enum class direction : uint8_t
            {
                NONE = 0x00,
                LEFT = (1 << 0),
                RIGHT = (1 << 1),
                TOP = (1 << 2),
                BOTTOM = (1 << 3),
                HOR = LEFT | RIGHT,
                VER = TOP | BOTTOM,
                ALL = HOR | VER,
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

            enum class part : uint32_t
            {
                MAIN = 0x000000,
                SCROLLBAR = 0x010000,
                INDICATOR = 0x020000,
                KNOB = 0x030000,
                SELECTED = 0x040000,
                ITEMS = 0x050000,
                CURSOR = 0x060000,
                CUSTOM_FIRST = 0x080000,
                ANY = 0x0F0000,
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

            class selector
            {
            public:
                selector(uint32_t value) : m_value(value) {}
                selector(part p) : m_value(static_cast<uint32_t>(p)) {}
                selector(state s) : m_value(static_cast<uint32_t>(s)) {}

                operator uint32_t() const { return m_value; }

                friend inline selector operator|(const selector &lhs, const selector &rhs)
                {
                    return lhs.m_value | rhs.m_value;
                }

            private:
                uint32_t m_value;
            };

            static int32_t SIZE_CONTENT();
            static int32_t PERCENTAGE(uint32_t percentage);
            static int32_t GRID_CONTENT();
            static int32_t GRID_FR(uint32_t fr);
            static int32_t GRID_TEMPLATE_LAST();

            object(object &parent);

            explicit object(lv_obj_t *lv_obj);

            virtual ~object();

            object(const object &) = delete;
            object(object &&) = delete;
            object &operator=(const object &) = delete;
            object &operator=(object &&) = delete;

            object &add_flag(const flag f);
            object &remove_flag(const flag f);
            bool has_flag(const flag f);

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
            object &coords(int32_t *x1, int32_t *y1, int32_t *x2 = nullptr, int32_t *y2 = nullptr);

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

            object &add_style(const style &stl, selector sel = 0);
            object &remove_style(const style &stl, selector sel = 0);
            object &clear_styles();

            object &invalidate_area(const int32_t x1, const int32_t y1, const int32_t x2, const int32_t y2);
            object &invalidate();

            bool is_visible();

            object &add_event_callback(event::code c, const event::callback &callback, void *user_data = nullptr);
            object &send_event(event::code c, void *parameter = nullptr);

            state get_state();
            bool has_state(state s);
            object &add_state(state s);
            object &remove_state(state s);

            int32_t index();
            object &set_index(int32_t index);

            object *parent();
            object &set_parent(object &parent);

            object *child(int32_t index = 0);
            uint32_t child_count();

            object *sibling(int32_t index = 1);

            screen &screen();
            group *group();

            lv_obj_t *lv_object() const;

        protected:
            static object &from_lv_object(lv_obj_t *lv_obj);

        private:
            static std::unordered_map<lv_obj_t *, object *, std::hash<lv_obj_t *>, std::equal_to<lv_obj_t *>, allocator<std::pair<lv_obj_t *const, object *>>> s_objects;

            lv_obj_t *mp_object;

            std::vector<event::descriptor *, allocator<event::descriptor *>> m_event_descriptors;

            friend class event;
            friend class group;

            friend bool operator==(const object &lhs, const object &rhs);
            friend bool operator!=(const object &lhs, const object &rhs);
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

        inline object::flag &operator|=(object::flag &lhs, const object::flag rhs)
        {
            lhs = lhs | rhs;

            return lhs;
        }

        inline object::flag &operator&=(object::flag &lhs, const object::flag rhs)
        {
            lhs = lhs & rhs;

            return lhs;
        }

        inline object::flag &operator^=(object::flag &lhs, const object::flag rhs)
        {
            lhs = lhs ^ rhs;

            return lhs;
        }

        inline object::selector operator|(const object::part lhs, const object::part rhs)
        {
            return static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs);
        }

        inline object::selector operator|(const object::state lhs, const object::state rhs)
        {
            return static_cast<uint16_t>(lhs) | static_cast<uint16_t>(rhs);
        }

        inline object::selector operator|(const object::part lhs, const object::state rhs)
        {
            return static_cast<uint32_t>(lhs) | static_cast<uint16_t>(rhs);
        }

        inline object::selector operator|(const object::state lhs, const object::part rhs)
        {
            return static_cast<uint16_t>(lhs) | static_cast<uint32_t>(rhs);
        }

        inline bool operator==(const object &lhs, const object &rhs)
        {
            return lhs.lv_object() == rhs.lv_object();
        }

        inline bool operator!=(const object &lhs, const object &rhs)
        {
            return !(lhs == rhs);
        }
    }
}