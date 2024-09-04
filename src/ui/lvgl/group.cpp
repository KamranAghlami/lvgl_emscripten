#include "ui/lvgl/group.h"

#include <cassert>

#include <lvgl.h>

#include "application/application.h"
#include "ui/lvgl/object.h"

namespace ui
{
    namespace lvgl
    {
        std::unordered_map<void *, group *> group::s_groups;

        void group::focus_object(object &obj)
        {
            lv_group_focus_obj(static_cast<lv_obj_t *>(obj.lv_object()));
        }

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
            lv_group_delete(static_cast<lv_group_t *>(mp_group));

            s_groups.erase(mp_group);
        }

        group &group::add_object(object &obj)
        {
            lv_group_add_obj(static_cast<lv_group_t *>(mp_group), static_cast<lv_obj_t *>(obj.lv_object()));

            return *this;
        }

        group &group::activate()
        {
            application::get()->set_active_group(*this);

            return *this;
        }

        void *group::lv_group()
        {
            return mp_group;
        }
    }
}