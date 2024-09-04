#include "ui/lvgl/group.h"

#include <cassert>

#include <lvgl.h>

#include "application/application.h"

namespace ui
{
    namespace lvgl
    {
        std::unordered_map<void *, group *> group::s_groups;

        group &group::from_lv_group(void *lv_grp)
        {
            auto it = s_groups.find(lv_grp);

            assert(it != s_groups.end());

            return *it->second;
        }

        group::group() : mp_group(lv_group_create())
        {
            s_groups.emplace(mp_group, this);
        }

        group::~group()
        {
            s_groups.erase(mp_group);
        }

        void group::activate()
        {
            application::get()->set_active_group(*this);
        }

        void *group::lv_group()
        {
            return mp_group;
        }
    }
}