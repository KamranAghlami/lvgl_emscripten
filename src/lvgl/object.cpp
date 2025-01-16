#include "lvgl/object.h"

#include <cassert>
#include <lvgl.h>

#include "lvgl/screen.h"
#include "lvgl/style.h"

namespace lvgl
{
    driver::memory::unordered_map<lv_obj_t *, object *> object::s_objects;

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

    object &object::from_lv_object(lv_obj_t *lv_obj)
    {
        auto it = s_objects.find(lv_obj);

        assert(it != s_objects.end());

        return *it->second;
    }

    object::object(object &parent) : mp_object(lv_obj_create(parent.mp_object))
    {
        s_objects.emplace(mp_object, this);
    }

    object::object(lv_obj_t *lv_obj) : mp_object(lv_obj)
    {
        s_objects.emplace(mp_object, this);
    }

    object::~object()
    {
        lv_obj_delete(mp_object);

        for (auto dsc : m_event_descriptors)
        {
            dsc->~descriptor();

            driver::memory::free(dsc);
        }

        s_objects.erase(mp_object);
    }

    lv_obj_t *object::lv_object() const
    {
        return mp_object;
    }

    object &object::add_flag(const flag f)
    {
        lv_obj_add_flag(mp_object, static_cast<lv_obj_flag_t>(f));

        return *this;
    }

    object &object::remove_flag(const flag f)
    {
        lv_obj_remove_flag(mp_object, static_cast<lv_obj_flag_t>(f));

        return *this;
    }

    bool object::has_flag(const flag f)
    {
        return lv_obj_has_flag(mp_object, static_cast<lv_obj_flag_t>(f));
    }

    object &object::set_x(const int32_t x)
    {
        lv_obj_set_x(mp_object, x);

        return *this;
    }

    object &object::set_y(const int32_t y)
    {
        lv_obj_set_y(mp_object, y);

        return *this;
    }

    object &object::set_pos(const int32_t x, const int32_t y)
    {
        lv_obj_set_pos(mp_object, x, y);

        return *this;
    }

    object &object::set_width(const int32_t width)
    {
        lv_obj_set_width(mp_object, width);

        return *this;
    }

    object &object::set_height(const int32_t height)
    {
        lv_obj_set_height(mp_object, height);

        return *this;
    }

    object &object::set_size(const int32_t width, const int32_t height)
    {
        lv_obj_set_size(mp_object, width, height);

        return *this;
    }

    int32_t object::x()
    {
        return lv_obj_get_x(mp_object);
    }

    int32_t object::y()
    {
        return lv_obj_get_y(mp_object);
    }

    int32_t object::width()
    {
        return lv_obj_get_width(mp_object);
    }

    int32_t object::height()
    {
        return lv_obj_get_height(mp_object);
    }

    object &object::coords(int32_t *x1, int32_t *y1, int32_t *x2, int32_t *y2)
    {
        lv_area_t lv_coords;

        lv_obj_get_coords(lv_object(), &lv_coords);

        if (x1)
            *x1 = lv_coords.x1;

        if (y1)
            *y1 = lv_coords.y1;

        if (x2)
            *x2 = lv_coords.x2;

        if (y2)
            *y2 = lv_coords.y2;

        return *this;
    }

    object &object::align(const alignment align, const int32_t x_ofs, const int32_t y_ofs)
    {
        lv_obj_align(mp_object, static_cast<lv_align_t>(align), x_ofs, y_ofs);

        return *this;
    }

    object &object::align_to(const object &base, const alignment align, const int32_t x_ofs, const int32_t y_ofs)
    {
        lv_obj_align_to(mp_object, base.mp_object, static_cast<lv_align_t>(align), x_ofs, y_ofs);

        return *this;
    }

    object &object::set_layout(layout l)
    {
        lv_obj_set_layout(mp_object, static_cast<lv_layout_t>(l));

        return *this;
    }

    object &object::update_layout()
    {
        lv_obj_update_layout(mp_object);

        return *this;
    }

    object &object::set_flex_flow(flex_flow f)
    {
        lv_obj_set_flex_flow(mp_object, static_cast<lv_flex_flow_t>(f));

        return *this;
    }

    object &object::set_flex_align(flex_alignment main, flex_alignment cross, flex_alignment track_cross)
    {
        lv_obj_set_flex_align(
            mp_object,
            static_cast<lv_flex_align_t>(main),
            static_cast<lv_flex_align_t>(cross),
            static_cast<lv_flex_align_t>(track_cross));

        return *this;
    }

    object &object::set_flex_grow(uint8_t grow)
    {
        lv_obj_set_flex_grow(mp_object, grow);

        return *this;
    }

    object &object::set_grid_dsc_array(const int32_t col_dsc[], const int32_t row_dsc[])
    {
        lv_obj_set_grid_dsc_array(mp_object, col_dsc, row_dsc);

        return *this;
    }

    object &object::set_grid_align(grid_alignment column, grid_alignment row)
    {
        lv_obj_set_grid_align(mp_object, static_cast<lv_grid_align_t>(column), static_cast<lv_grid_align_t>(row));

        return *this;
    }

    object &object::set_grid_cell(grid_alignment column, int32_t col_pos, int32_t col_span,
                                  grid_alignment row, int32_t row_pos, int32_t row_span)
    {
        lv_obj_set_grid_cell(mp_object,
                             static_cast<lv_grid_align_t>(column), col_pos, col_span,
                             static_cast<lv_grid_align_t>(row), row_pos, row_span);

        return *this;
    }

    object &object::set_scrollbar_mode(scrollbar_mode mode)
    {
        lv_obj_set_scrollbar_mode(mp_object, static_cast<lv_scrollbar_mode_t>(mode));

        return *this;
    }

    object &object::add_style(const style &stl, selector sel)
    {
        lv_obj_add_style(mp_object, static_cast<const lv_style_t *>(stl.mp_style), static_cast<lv_style_selector_t>(sel));

        return *this;
    }

    object &object::remove_style(const style &stl, selector sel)
    {
        lv_obj_remove_style(mp_object, static_cast<const lv_style_t *>(stl.mp_style), static_cast<lv_style_selector_t>(sel));

        return *this;
    }

    object &object::clear_styles()
    {
        lv_obj_remove_style_all(mp_object);

        return *this;
    }

    object &object::invalidate_area(const int32_t x1, const int32_t y1, const int32_t x2, const int32_t y2)
    {
        const lv_area_t area{
            .x1 = x1,
            .y1 = y1,
            .x2 = x2,
            .y2 = y2,
        };

        lv_obj_invalidate_area(mp_object, &area);

        return *this;
    }

    object &object::invalidate()
    {
        lv_obj_invalidate(mp_object);

        return *this;
    }

    bool object::is_visible()
    {
        return lv_obj_is_visible(mp_object);
    }

    object &object::add_event_callback(event::code c, const event::callback &callback, void *user_data)
    {
        auto proxy_callback = [](lv_event_t *lv_event)
        {
            event e(lv_event);

            static_cast<event::descriptor *>(lv_event_get_user_data(lv_event))->m_callback(e);
        };

        auto dsc_mem = driver::memory::allocate(sizeof(event::descriptor));
        auto dsc = new (dsc_mem) event::descriptor(callback, user_data);

        dsc->mp_descriptor = lv_obj_add_event_cb(mp_object, proxy_callback, static_cast<lv_event_code_t>(c), dsc);

        m_event_descriptors.push_back(dsc);

        return *this;
    }

    object &object::send_event(event::code c, void *parameter)
    {
        lv_obj_send_event(mp_object, static_cast<lv_event_code_t>(c), parameter);

        return *this;
    }

    object::state object::get_state()
    {
        return static_cast<object::state>(lv_obj_get_state(mp_object));
    }

    bool object::has_state(state s)
    {
        return lv_obj_has_state(mp_object, static_cast<lv_state_t>(s));
    }

    object &object::add_state(state s)
    {
        lv_obj_add_state(mp_object, static_cast<lv_state_t>(s));

        return *this;
    }

    object &object::remove_state(state s)
    {
        lv_obj_remove_state(mp_object, static_cast<lv_state_t>(s));

        return *this;
    }

    int32_t object::index()
    {
        return lv_obj_get_index(mp_object);
    }

    object &object::set_index(int32_t index)
    {
        lv_obj_move_to_index(mp_object, index);

        return *this;
    }

    object *object::get_parent()
    {
        auto lv_parent = lv_obj_get_parent(mp_object);

        return lv_parent ? &from_lv_object(lv_parent) : nullptr;
    }

    object &object::set_parent(object &parent)
    {
        lv_obj_set_parent(mp_object, parent.mp_object);

        return *this;
    }

    object *object::child(int32_t index)
    {
        auto lv_child = lv_obj_get_child(mp_object, index);

        return lv_child ? &from_lv_object(lv_child) : nullptr;
    }

    uint32_t object::child_count()
    {
        return lv_obj_get_child_count(mp_object);
    }

    object *object::sibling(int32_t index)
    {
        auto lv_sibling = lv_obj_get_sibling(mp_object, index);

        return lv_sibling ? &from_lv_object(lv_sibling) : nullptr;
    }

    screen &object::screen()
    {
        auto lv_screen = lv_obj_get_screen(mp_object);

        return static_cast<lvgl::screen &>(object::from_lv_object(lv_screen));
    }

    group *object::group()
    {
        auto lv_group = lv_obj_get_group(mp_object);

        return lv_group ? &group::from_lv_group(lv_group) : nullptr;
    }
}
