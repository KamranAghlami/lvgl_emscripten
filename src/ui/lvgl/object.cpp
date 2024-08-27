#include "ui/lvgl/object.h"

#include <cassert>
#include "lvgl.h"

namespace ui
{
    namespace lvgl
    {
        std::unordered_map<void *, object *> object::s_objects;

        object &object::from_lv_object(void *lv_obj)
        {
            auto it = s_objects.find(lv_obj);

            assert(it != s_objects.end());

            return *it->second;
        }

        object::object(object *parent) : mp_object(lv_obj_create(parent ? static_cast<lv_obj_t *>(parent->mp_object) : nullptr))
        {
            s_objects.emplace(mp_object, this);

            lv_obj_set_style_bg_color(static_cast<lv_obj_t *>(mp_object),
                                      lv_color_make(lv_rand(0, 0xFF),
                                                    lv_rand(0, 0xFF),
                                                    lv_rand(0, 0xFF)),
                                      LV_PART_MAIN | LV_STATE_DEFAULT);
        }

        object::object(void *lv_obj) : mp_object(lv_obj)
        {
            s_objects.emplace(mp_object, this);
        }

        object::~object()
        {
            lv_obj_delete(static_cast<lv_obj_t *>(mp_object));

            for (auto event_descriptor : m_event_descriptors)
                delete event_descriptor;

            s_objects.erase(mp_object);
        }

        void *object::lv_object()
        {
            return mp_object;
        }

        object &object::add_flag(const flag f)
        {
            lv_obj_add_flag(static_cast<lv_obj_t *>(mp_object), static_cast<lv_obj_flag_t>(f));

            return *this;
        }

        object &object::remove_flag(const flag f)
        {
            lv_obj_remove_flag(static_cast<lv_obj_t *>(mp_object), static_cast<lv_obj_flag_t>(f));

            return *this;
        }

        bool object::has_flag(const flag f)
        {
            return lv_obj_has_flag(static_cast<lv_obj_t *>(mp_object), static_cast<lv_obj_flag_t>(f));
        }

        object &object::add_state(const state s)
        {
            lv_obj_add_state(static_cast<lv_obj_t *>(mp_object), static_cast<lv_state_t>(s));

            return *this;
        }

        object &object::remove_state(const state s)
        {
            lv_obj_remove_state(static_cast<lv_obj_t *>(mp_object), static_cast<lv_state_t>(s));

            return *this;
        }

        bool object::has_state(const state s)
        {
            return lv_obj_has_state(static_cast<lv_obj_t *>(mp_object), static_cast<lv_state_t>(s));
        }

        object &object::set_x(const int32_t x)
        {
            lv_obj_set_x(static_cast<lv_obj_t *>(mp_object), x);

            return *this;
        }

        object &object::set_y(const int32_t y)
        {
            lv_obj_set_y(static_cast<lv_obj_t *>(mp_object), y);

            return *this;
        }

        object &object::set_pos(const int32_t x, const int32_t y)
        {
            lv_obj_set_pos(static_cast<lv_obj_t *>(mp_object), x, y);

            return *this;
        }

        object &object::set_width(const int32_t width)
        {
            lv_obj_set_width(static_cast<lv_obj_t *>(mp_object), width);

            return *this;
        }

        object &object::set_height(const int32_t height)
        {
            lv_obj_set_height(static_cast<lv_obj_t *>(mp_object), height);

            return *this;
        }

        object &object::set_size(const int32_t width, const int32_t height)
        {
            lv_obj_set_size(static_cast<lv_obj_t *>(mp_object), width, height);

            return *this;
        }

        int32_t object::x()
        {
            return lv_obj_get_x(static_cast<lv_obj_t *>(mp_object));
        }

        int32_t object::y()
        {
            return lv_obj_get_y(static_cast<lv_obj_t *>(mp_object));
        }

        int32_t object::width()
        {
            return lv_obj_get_width(static_cast<lv_obj_t *>(mp_object));
        }

        int32_t object::height()
        {
            return lv_obj_get_height(static_cast<lv_obj_t *>(mp_object));
        }

        object &object::align(const alignment align, const int32_t x_ofs, const int32_t y_ofs)
        {
            lv_obj_align(static_cast<lv_obj_t *>(mp_object), static_cast<lv_align_t>(align), x_ofs, y_ofs);

            return *this;
        }

        object &object::align_to(const object &base, const alignment align, const int32_t x_ofs, const int32_t y_ofs)
        {
            lv_obj_align_to(static_cast<lv_obj_t *>(mp_object), static_cast<lv_obj_t *>(base.mp_object), static_cast<lv_align_t>(align), x_ofs, y_ofs);

            return *this;
        }

        object &object::invalidate()
        {
            lv_obj_invalidate(static_cast<lv_obj_t *>(mp_object));

            return *this;
        }

        bool object::is_visible()
        {
            return lv_obj_is_visible(static_cast<lv_obj_t *>(mp_object));
        }

        void object::add_event_callback(event::code code, const event::callback &callback)
        {
            auto proxy_callback = [](lv_event_t *lv_event)
            {
                lv_obj_t *lv_target_current = lv_event_get_current_target_obj(lv_event);
                lv_obj_t *lv_target = lv_event_get_target_obj(lv_event);

                const bool bubbled = lv_target_current != lv_target;

                object &current_target = from_lv_object(lv_target_current);
                object &original_target = bubbled ? from_lv_object(lv_target) : current_target;

                event e{
                    .m_code = static_cast<event::code>(lv_event_get_code(lv_event)),
                    .m_current_target = current_target,
                    .m_original_target = original_target,
                };

                static_cast<event::descriptor *>(lv_event_get_user_data(lv_event))->m_callback(e);
            };

            auto dsc = new event::descriptor(callback);

            dsc->mp_descriptor = lv_obj_add_event_cb(static_cast<lv_obj_t *>(mp_object), proxy_callback, static_cast<lv_event_code_t>(code), dsc);

            m_event_descriptors.push_back(dsc);
        }
    };
}