#pragma once

#include <unordered_map>

namespace ui
{
    namespace lvgl
    {
        class object;

        class group
        {
        public:
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

            static void focus_object(object &obj);

            group();
            ~group();

            group(const group &) = delete;
            group(group &&) = delete;
            group &operator=(const group &) = delete;
            group &operator=(group &&) = delete;

            group &add_object(object &obj);

            group &activate();

            void *lv_group();

        private:
            static group &from_lv_group(void *lv_grp);

            static std::unordered_map<void *, group *> s_groups;

            void *mp_group;

            friend class object;
        };

    }
}