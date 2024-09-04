#pragma once

#include <unordered_map>

namespace ui
{
    namespace lvgl
    {
        class group
        {
        public:
            group();
            ~group();

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