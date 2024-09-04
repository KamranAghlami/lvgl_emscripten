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
            static void focus_object(object &obj);

            group();
            ~group();

            group(const group &) = delete;
            group(group &&) = delete;
            group &operator=(const group &) = delete;
            group &operator=(group &&) = delete;

            void add_object(object &obj);

            void activate();

            void *lv_group();

        private:
            static group &from_lv_group(void *lv_grp);

            static std::unordered_map<void *, group *> s_groups;

            void *mp_group;

            friend class object;
        };

    }
}