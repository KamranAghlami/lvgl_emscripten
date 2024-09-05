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

        void group::set_default(group &grp)
        {
            lv_group_set_default(static_cast<lv_group_t *>(grp.mp_group));
        }

        group *group::get_default()
        {
            auto lv_group = lv_group_get_default();

            return lv_group ? &from_lv_group(lv_group) : nullptr;
        }

        void group::swap_object(object &obj1, object &obj2)
        {
            lv_group_swap_obj(static_cast<lv_obj_t *>(obj1.lv_object()), static_cast<lv_obj_t *>(obj2.lv_object()));
        }

        void group::remove_object(object &obj)
        {
            lv_group_remove_obj(static_cast<lv_obj_t *>(obj.lv_object()));
        }

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

        group &group::remove_all_objects()
        {
            lv_group_remove_all_objs(static_cast<lv_group_t *>(mp_group));

            return *this;
        }

        group &group::focus_next()
        {
            lv_group_focus_next(static_cast<lv_group_t *>(mp_group));

            return *this;
        }

        group &group::focus_previous()
        {
            lv_group_focus_prev(static_cast<lv_group_t *>(mp_group));

            return *this;
        }

        group &group::focus_freeze(bool enable)
        {
            lv_group_focus_freeze(static_cast<lv_group_t *>(mp_group), enable);

            return *this;
        }

        group &group::send_data(uint32_t key)
        {
            lv_group_send_data(static_cast<lv_group_t *>(mp_group), key);

            return *this;
        }

        group &group::send_data(key_code code)
        {
            return send_data(static_cast<uint32_t>(code));
        }

        object *group::get_focused()
        {
            auto lv_obj = lv_group_get_focused(static_cast<lv_group_t *>(mp_group));

            return lv_obj ? &object::from_lv_object(lv_obj) : nullptr;
        }

        object *group::get_object_by_index(uint32_t index)
        {
            auto lv_obj = lv_group_get_obj_by_index(static_cast<lv_group_t *>(mp_group), index);

            return lv_obj ? &object::from_lv_object(lv_obj) : nullptr;
        }

        uint32_t group::get_object_count()
        {
            return lv_group_get_obj_count(static_cast<lv_group_t *>(mp_group));
        }

        group &group::set_refocus_policy(refocus_policy policy)
        {
            lv_group_set_refocus_policy(static_cast<lv_group_t *>(mp_group), static_cast<lv_group_refocus_policy_t>(policy));

            return *this;
        }

        group &group::set_focus_callback(focus_callback cb)
        {
            m_focus_callback = cb;

            auto on_focus = [](lv_group_t *lv_grp)
            {
                auto &grp = from_lv_group(lv_grp);

                grp.m_focus_callback(grp);
            };

            lv_group_set_focus_cb(static_cast<lv_group_t *>(mp_group), cb ? on_focus : nullptr);

            return *this;
        }

        group &group::set_edge_callback(edge_callback cb)
        {
            m_edge_callback = cb;

            auto on_edge = [](lv_group_t *lv_grp, bool forward)
            {
                auto &grp = from_lv_group(lv_grp);

                grp.m_edge_callback(grp, forward);
            };

            lv_group_set_edge_cb(static_cast<lv_group_t *>(mp_group), cb ? on_edge : nullptr);

            return *this;
        }

        group &group::set_editing(bool enable)
        {
            lv_group_set_editing(static_cast<lv_group_t *>(mp_group), enable);

            return *this;
        }

        group &group::set_wrap(bool enable)
        {
            lv_group_set_wrap(static_cast<lv_group_t *>(mp_group), enable);

            return *this;
        }

        group::focus_callback group::get_focus_callback()
        {
            return m_focus_callback;
        }

        group::edge_callback group::get_edge_callback()
        {
            return m_edge_callback;
        }

        bool group::get_editing()
        {
            return lv_group_get_editing(static_cast<lv_group_t *>(mp_group));
        }

        bool group::get_wrap()
        {
            return lv_group_get_wrap(static_cast<lv_group_t *>(mp_group));
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