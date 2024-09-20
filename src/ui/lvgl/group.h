#pragma once

#include <unordered_map>
#include <functional>

#include "ui/lvgl/memory.h"

extern "C"
{
    struct lv_group_t;
}

namespace ui
{
    namespace lvgl
    {
        class object;

        class group
        {
        public:
            using focus_callback = std::function<void(group &)>;
            using edge_callback = std::function<void(group &, bool)>;

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

            enum class refocus_policy : uint8_t
            {
                NEXT,
                PREV,
            };

            static void set_default(group &grp);
            static group *get_default();

            static void swap_object(object &obj1, object &obj2);
            static void remove_object(object &obj);
            static void focus_object(object &obj);

            group();
            ~group();

            group(const group &) = delete;
            group(group &&) = delete;
            group &operator=(const group &) = delete;
            group &operator=(group &&) = delete;

            group &add_object(object &obj);
            group &remove_all_objects();
            group &focus_next();
            group &focus_previous();
            group &focus_freeze(bool enable);
            group &send_data(uint32_t key);
            group &send_data(key_code code);

            object *get_focused();
            object *get_object_by_index(uint32_t index);
            uint32_t get_object_count();

            group &set_refocus_policy(refocus_policy policy);
            group &set_focus_callback(const focus_callback &cb);
            group &set_edge_callback(const edge_callback &cb);
            group &set_editing(bool enable);
            group &set_wrap(bool enable);

            const focus_callback &get_focus_callback();
            const edge_callback &get_edge_callback();
            bool get_editing();
            bool get_wrap();

            lv_group_t *lv_group();

        private:
            static group &from_lv_group(lv_group_t *lv_grp);

            static std::unordered_map<lv_group_t *, group *, std::hash<lv_group_t *>, std::equal_to<lv_group_t *>, allocator<std::pair<lv_group_t *const, group *>>> s_groups;

            lv_group_t *mp_group;
            focus_callback m_focus_callback = nullptr;
            edge_callback m_edge_callback = nullptr;

            friend class object;
        };

    }
}