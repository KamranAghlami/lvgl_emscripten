#include "ui/lvgl/object.h"

#include <cassert>
#include <lvgl.h>

#include "ui/lvgl/screen.h"

namespace ui
{
    namespace lvgl
    {
        std::unordered_map<void *, object *> object::s_objects;

        int32_t object::SIZE_CONTENT()
        {
            return LV_SIZE_CONTENT;
        }

        int32_t object::PERCENTAGE(uint32_t percentage)
        {
            return LV_PCT(percentage);
        }

        int32_t object::GRID_CONTENT()
        {
            return LV_GRID_CONTENT;
        }

        int32_t object::GRID_FR(uint32_t fr)
        {
            return LV_GRID_FR(fr);
        }

        int32_t object::GRID_TEMPLATE_LAST()
        {
            return LV_GRID_TEMPLATE_LAST;
        }

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

            for (auto dsc : m_event_descriptors)
            {
                dsc->~descriptor();

                lv_free(dsc);
            }

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

        object &object::set_layout(layout l)
        {
            lv_obj_set_layout(static_cast<lv_obj_t *>(mp_object), static_cast<lv_layout_t>(l));

            return *this;
        }

        object &object::update_layout()
        {
            lv_obj_update_layout(static_cast<lv_obj_t *>(mp_object));

            return *this;
        }

        object &object::set_flex_flow(flex_flow f)
        {
            lv_obj_set_flex_flow(static_cast<lv_obj_t *>(mp_object), static_cast<lv_flex_flow_t>(f));

            return *this;
        }

        object &object::set_flex_align(flex_alignment main, flex_alignment cross, flex_alignment track_cross)
        {
            lv_obj_set_flex_align(
                static_cast<lv_obj_t *>(mp_object),
                static_cast<lv_flex_align_t>(main),
                static_cast<lv_flex_align_t>(cross),
                static_cast<lv_flex_align_t>(track_cross));

            return *this;
        }

        object &object::set_flex_grow(uint8_t grow)
        {
            lv_obj_set_flex_grow(static_cast<lv_obj_t *>(mp_object), grow);

            return *this;
        }

        object &object::set_grid_dsc_array(const int32_t col_dsc[], const int32_t row_dsc[])
        {
            lv_obj_set_grid_dsc_array(static_cast<lv_obj_t *>(mp_object), col_dsc, row_dsc);

            return *this;
        }

        object &object::set_grid_align(grid_alignment column, grid_alignment row)
        {
            lv_obj_set_grid_align(static_cast<lv_obj_t *>(mp_object), static_cast<lv_grid_align_t>(column), static_cast<lv_grid_align_t>(row));

            return *this;
        }

        object &object::set_grid_cell(grid_alignment column, int32_t col_pos, int32_t col_span,
                                      grid_alignment row, int32_t row_pos, int32_t row_span)
        {
            lv_obj_set_grid_cell(static_cast<lv_obj_t *>(mp_object),
                                 static_cast<lv_grid_align_t>(column), col_pos, col_span,
                                 static_cast<lv_grid_align_t>(row), row_pos, row_span);

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

        void object::add_event_callback(event::code c, const event::callback &callback, void *user_data)
        {
            auto proxy_callback = [](lv_event_t *lv_event)
            {
                lv_obj_t *lv_target_current = lv_event_get_current_target_obj(lv_event);
                lv_obj_t *lv_target = lv_event_get_target_obj(lv_event);

                const bool bubbled = lv_target_current != lv_target;

                object &current_target = from_lv_object(lv_target_current);
                object &original_target = bubbled ? from_lv_object(lv_target) : current_target;

                auto dsc = static_cast<event::descriptor *>(lv_event_get_user_data(lv_event));

                event e{
                    .m_code = static_cast<event::code>(lv_event_get_code(lv_event)),
                    .m_user_data = dsc->m_user_data,
                    .m_parameter = lv_event_get_param(lv_event),
                    .m_current_target = current_target,
                    .m_original_target = original_target,
                };

                dsc->m_callback(e);
            };

            auto dsc_mem = lv_malloc(sizeof(event::descriptor));
            auto dsc = new (dsc_mem) event::descriptor(callback, user_data);

            dsc->mp_descriptor = lv_obj_add_event_cb(static_cast<lv_obj_t *>(mp_object), proxy_callback, static_cast<lv_event_code_t>(c), dsc);

            m_event_descriptors.push_back(dsc);
        }

        void object::send_event(event::code c, void *parameter)
        {
            lv_obj_send_event(static_cast<lv_obj_t *>(mp_object), static_cast<lv_event_code_t>(c), parameter);
        }

        int32_t object::index()
        {
            return lv_obj_get_index(static_cast<lv_obj_t *>(mp_object));
        }

        void object::set_index(int32_t index)
        {
            lv_obj_move_to_index(static_cast<lv_obj_t *>(mp_object), index);
        }

        object *object::parent()
        {
            auto lv_parent = lv_obj_get_parent(static_cast<lv_obj_t *>(mp_object));

            return lv_parent ? &from_lv_object(lv_parent) : nullptr;
        }

        void object::set_parent(object &parent)
        {
            lv_obj_set_parent(static_cast<lv_obj_t *>(mp_object), static_cast<lv_obj_t *>(parent.mp_object));
        }

        object *object::child(int32_t index)
        {
            auto lv_child = lv_obj_get_child(static_cast<lv_obj_t *>(mp_object), index);

            return lv_child ? &from_lv_object(lv_child) : nullptr;
        }

        uint32_t object::child_count()
        {
            return lv_obj_get_child_count(static_cast<lv_obj_t *>(mp_object));
        }

        object *object::sibling(int32_t index)
        {
            auto lv_sibling = lv_obj_get_sibling(static_cast<lv_obj_t *>(mp_object), index);

            return lv_sibling ? &from_lv_object(lv_sibling) : nullptr;
        }

        screen &object::screen()
        {
            auto lv_screen = lv_obj_get_screen(static_cast<lv_obj_t *>(mp_object));

            return static_cast<lvgl::screen &>(object::from_lv_object(lv_screen));
        }

        group *object::group()
        {
            auto lv_group = lv_obj_get_group(static_cast<lv_obj_t *>(mp_object));

            return lv_group ? &group::from_lv_group(lv_group) : nullptr;
        }
    };
}