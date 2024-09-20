#include "ui/lvgl/style.h"

#define _lv_style static_cast<lv_style_t *>(mp_style)
#define _lv_color(c) lv_color_make((c).red(), (c).green(), (c).blue())

#include <lvgl.h>

#include "ui/lvgl/memory.h"

namespace ui
{
    namespace lvgl
    {
        style::style() : mp_style(lvgl::malloc(sizeof(lv_style_t)))
        {
            lv_style_init(_lv_style);
        }

        style::~style()
        {
            lv_style_reset(_lv_style);

            lvgl::free(mp_style);
        }

        style &style::set_width(int32_t v)
        {
            lv_style_set_width(_lv_style, v);

            return *this;
        }

        style &style::set_min_width(int32_t v)
        {
            lv_style_set_min_width(_lv_style, v);

            return *this;
        }

        style &style::set_max_width(int32_t v)
        {
            lv_style_set_max_width(_lv_style, v);

            return *this;
        }

        style &style::set_height(int32_t v)
        {
            lv_style_set_height(_lv_style, v);

            return *this;
        }

        style &style::set_min_height(int32_t v)
        {
            lv_style_set_min_height(_lv_style, v);

            return *this;
        }

        style &style::set_max_height(int32_t v)
        {
            lv_style_set_max_height(_lv_style, v);

            return *this;
        }

        style &style::set_length(int32_t v)
        {
            lv_style_set_length(_lv_style, v);

            return *this;
        }

        style &style::set_x(int32_t v)
        {
            lv_style_set_x(_lv_style, v);

            return *this;
        }

        style &style::set_y(int32_t v)
        {
            lv_style_set_y(_lv_style, v);

            return *this;
        }

        style &style::set_align(object::alignment v)
        {
            lv_style_set_align(_lv_style, static_cast<lv_align_t>(v));

            return *this;
        }

        style &style::set_transform_width(int32_t v)
        {
            lv_style_set_transform_width(_lv_style, v);

            return *this;
        }

        style &style::set_transform_height(int32_t v)
        {
            lv_style_set_transform_height(_lv_style, v);

            return *this;
        }

        style &style::set_translate_x(int32_t v)
        {
            lv_style_set_translate_x(_lv_style, v);

            return *this;
        }

        style &style::set_translate_y(int32_t v)
        {
            lv_style_set_translate_y(_lv_style, v);

            return *this;
        }

        style &style::set_transform_scale_x(int32_t v)
        {
            lv_style_set_transform_scale_x(_lv_style, v);

            return *this;
        }

        style &style::set_transform_scale_y(int32_t v)
        {
            lv_style_set_transform_scale_y(_lv_style, v);

            return *this;
        }

        style &style::set_transform_rotation(int32_t v)
        {
            lv_style_set_transform_rotation(_lv_style, v);

            return *this;
        }

        style &style::set_transform_pivot_x(int32_t v)
        {
            lv_style_set_transform_pivot_x(_lv_style, v);

            return *this;
        }

        style &style::set_transform_pivot_y(int32_t v)
        {
            lv_style_set_transform_pivot_y(_lv_style, v);

            return *this;
        }

        style &style::set_transform_skew_x(int32_t v)
        {
            lv_style_set_transform_skew_x(_lv_style, v);

            return *this;
        }

        style &style::set_transform_skew_y(int32_t v)
        {
            lv_style_set_transform_skew_y(_lv_style, v);

            return *this;
        }

        style &style::set_pad_top(int32_t v)
        {
            lv_style_set_pad_top(_lv_style, v);

            return *this;
        }

        style &style::set_pad_bottom(int32_t v)
        {
            lv_style_set_pad_bottom(_lv_style, v);

            return *this;
        }

        style &style::set_pad_left(int32_t v)
        {
            lv_style_set_pad_left(_lv_style, v);

            return *this;
        }

        style &style::set_pad_right(int32_t v)
        {
            lv_style_set_pad_right(_lv_style, v);

            return *this;
        }

        style &style::set_pad_row(int32_t v)
        {
            lv_style_set_pad_row(_lv_style, v);

            return *this;
        }

        style &style::set_pad_column(int32_t v)
        {
            lv_style_set_pad_column(_lv_style, v);

            return *this;
        }

        style &style::set_pad_all(int32_t value)
        {
            lv_style_set_pad_all(_lv_style, value);

            return *this;
        }

        style &style::set_pad_hor(int32_t value)
        {
            lv_style_set_pad_hor(_lv_style, value);

            return *this;
        }

        style &style::set_pad_ver(int32_t value)
        {
            lv_style_set_pad_ver(_lv_style, value);

            return *this;
        }

        style &style::set_pad_gap(int32_t value)
        {
            lv_style_set_pad_gap(_lv_style, value);

            return *this;
        }

        style &style::set_margin_top(int32_t v)
        {
            lv_style_set_margin_top(_lv_style, v);

            return *this;
        }

        style &style::set_margin_bottom(int32_t v)
        {
            lv_style_set_margin_bottom(_lv_style, v);

            return *this;
        }

        style &style::set_margin_left(int32_t v)
        {
            lv_style_set_margin_left(_lv_style, v);

            return *this;
        }

        style &style::set_margin_right(int32_t v)
        {
            lv_style_set_margin_right(_lv_style, v);

            return *this;
        }

        style &style::set_bg_color(const color &v)
        {
            lv_style_set_bg_color(_lv_style, _lv_color(v));

            return *this;
        }

        style &style::set_bg_opa(uint8_t v)
        {
            lv_style_set_bg_opa(_lv_style, v);

            return *this;
        }

        style &style::set_bg_grad_color(const color &v)
        {
            lv_style_set_bg_grad_color(_lv_style, _lv_color(v));

            return *this;
        }

        style &style::set_bg_grad_dir(gradiant_direction v)
        {
            lv_style_set_bg_grad_dir(_lv_style, static_cast<lv_grad_dir_t>(v));

            return *this;
        }

        style &style::set_bg_main_stop(int32_t v)
        {
            lv_style_set_bg_main_stop(_lv_style, v);

            return *this;
        }

        style &style::set_bg_grad_stop(int32_t v)
        {
            lv_style_set_bg_grad_stop(_lv_style, v);

            return *this;
        }

        style &style::set_bg_main_opa(uint8_t v)
        {
            lv_style_set_bg_main_opa(_lv_style, v);

            return *this;
        }

        style &style::set_bg_grad_opa(uint8_t v)
        {
            lv_style_set_bg_grad_opa(_lv_style, v);

            return *this;
        }

        style &style::set_bg_image_src(const void *v)
        {
            lv_style_set_bg_image_src(_lv_style, v);

            return *this;
        }

        style &style::set_bg_image_opa(uint8_t v)
        {
            lv_style_set_bg_image_opa(_lv_style, v);

            return *this;
        }

        style &style::set_bg_image_recolor(const color &v)
        {
            lv_style_set_bg_image_recolor(_lv_style, _lv_color(v));

            return *this;
        }

        style &style::set_bg_image_recolor_opa(uint8_t v)
        {
            lv_style_set_bg_image_recolor_opa(_lv_style, v);

            return *this;
        }

        style &style::set_bg_image_tiled(bool v)
        {
            lv_style_set_bg_image_tiled(_lv_style, v);

            return *this;
        }

        style &style::set_border_color(const color &v)
        {
            lv_style_set_border_color(_lv_style, _lv_color(v));

            return *this;
        }

        style &style::set_border_opa(uint8_t v)
        {
            lv_style_set_border_opa(_lv_style, v);

            return *this;
        }

        style &style::set_border_width(int32_t v)
        {
            lv_style_set_border_width(_lv_style, v);

            return *this;
        }

        style &style::set_border_side(border_side v)
        {
            lv_style_set_border_side(_lv_style, static_cast<lv_border_side_t>(v));

            return *this;
        }

        style &style::set_border_post(bool v)
        {
            lv_style_set_border_post(_lv_style, v);

            return *this;
        }

        style &style::set_outline_width(int32_t v)
        {
            lv_style_set_outline_width(_lv_style, v);

            return *this;
        }

        style &style::set_outline_color(const color &v)
        {
            lv_style_set_outline_color(_lv_style, _lv_color(v));

            return *this;
        }

        style &style::set_outline_opa(uint8_t v)
        {
            lv_style_set_outline_opa(_lv_style, v);

            return *this;
        }

        style &style::set_outline_pad(int32_t v)
        {
            lv_style_set_outline_pad(_lv_style, v);

            return *this;
        }

        style &style::set_shadow_width(int32_t v)
        {
            lv_style_set_shadow_width(_lv_style, v);

            return *this;
        }

        style &style::set_shadow_offset_x(int32_t v)
        {
            lv_style_set_shadow_offset_x(_lv_style, v);

            return *this;
        }

        style &style::set_shadow_offset_y(int32_t v)
        {
            lv_style_set_shadow_offset_y(_lv_style, v);

            return *this;
        }

        style &style::set_shadow_spread(int32_t v)
        {
            lv_style_set_shadow_spread(_lv_style, v);

            return *this;
        }

        style &style::set_shadow_color(const color &v)
        {
            lv_style_set_shadow_color(_lv_style, _lv_color(v));

            return *this;
        }

        style &style::set_shadow_opa(uint8_t v)
        {
            lv_style_set_shadow_opa(_lv_style, v);

            return *this;
        }

        style &style::set_image_opa(uint8_t v)
        {
            lv_style_set_image_opa(_lv_style, v);

            return *this;
        }

        style &style::set_image_recolor(const color &v)
        {
            lv_style_set_image_recolor(_lv_style, _lv_color(v));

            return *this;
        }

        style &style::set_image_recolor_opa(uint8_t v)
        {
            lv_style_set_image_recolor_opa(_lv_style, v);

            return *this;
        }

        style &style::set_line_width(int32_t v)
        {
            lv_style_set_line_width(_lv_style, v);

            return *this;
        }

        style &style::set_line_dash_width(int32_t v)
        {
            lv_style_set_line_dash_width(_lv_style, v);

            return *this;
        }

        style &style::set_line_dash_gap(int32_t v)
        {
            lv_style_set_line_dash_gap(_lv_style, v);

            return *this;
        }

        style &style::set_line_rounded(bool v)
        {
            lv_style_set_line_rounded(_lv_style, v);

            return *this;
        }

        style &style::set_line_color(const color &v)
        {
            lv_style_set_line_color(_lv_style, _lv_color(v));

            return *this;
        }

        style &style::set_line_opa(uint8_t v)
        {
            lv_style_set_line_opa(_lv_style, v);

            return *this;
        }

        style &style::set_arc_width(int32_t v)
        {
            lv_style_set_arc_width(_lv_style, v);

            return *this;
        }

        style &style::set_arc_rounded(bool v)
        {
            lv_style_set_arc_rounded(_lv_style, v);

            return *this;
        }

        style &style::set_arc_color(const color &v)
        {
            lv_style_set_arc_color(_lv_style, _lv_color(v));

            return *this;
        }

        style &style::set_arc_opa(uint8_t v)
        {
            lv_style_set_arc_opa(_lv_style, v);

            return *this;
        }

        style &style::set_arc_image_src(const void *v)
        {
            lv_style_set_arc_image_src(_lv_style, v);

            return *this;
        }

        style &style::set_text_color(const color &v)
        {
            lv_style_set_text_color(_lv_style, _lv_color(v));

            return *this;
        }

        style &style::set_text_opa(uint8_t v)
        {
            lv_style_set_text_opa(_lv_style, v);

            return *this;
        }

        style &style::set_text_font(const font &v)
        {
            lv_style_set_text_font(_lv_style, v.lv_font());

            return *this;
        }

        style &style::set_text_letter_space(int32_t v)
        {
            lv_style_set_text_letter_space(_lv_style, v);

            return *this;
        }

        style &style::set_text_line_space(int32_t v)
        {
            lv_style_set_text_line_space(_lv_style, v);

            return *this;
        }

        style &style::set_text_decor(text_decor v)
        {
            lv_style_set_text_decor(_lv_style, static_cast<lv_text_decor_t>(v));

            return *this;
        }

        style &style::set_text_align(text_alignment v)
        {
            lv_style_set_text_align(_lv_style, static_cast<lv_text_align_t>(v));

            return *this;
        }

        style &style::set_radius(int32_t v)
        {
            lv_style_set_radius(_lv_style, v);

            return *this;
        }

        style &style::set_clip_corner(bool v)
        {
            lv_style_set_clip_corner(_lv_style, v);

            return *this;
        }

        style &style::set_opa(uint8_t v)
        {
            lv_style_set_opa(_lv_style, v);

            return *this;
        }

        style &style::set_opa_layered(uint8_t v)
        {
            lv_style_set_opa_layered(_lv_style, v);

            return *this;
        }

        style &style::set_color_filter_opa(uint8_t v)
        {
            lv_style_set_color_filter_opa(_lv_style, v);

            return *this;
        }

        style &style::set_anim(const animation &v)
        {
            lv_style_set_anim(_lv_style, v.lv_animation());

            return *this;
        }

        style &style::set_anim_duration(uint32_t v)
        {
            lv_style_set_anim_duration(_lv_style, v);

            return *this;
        }

        style &style::set_blend_mode(blend_mode v)
        {
            lv_style_set_blend_mode(_lv_style, static_cast<lv_blend_mode_t>(v));

            return *this;
        }

        style &style::set_layout(uint16_t v)
        {
            lv_style_set_layout(_lv_style, v);

            return *this;
        }

        style &style::set_base_dir(base_direction v)
        {
            lv_style_set_base_dir(_lv_style, static_cast<lv_base_dir_t>(v));

            return *this;
        }

        style &style::set_bitmap_mask_src(const void *v)
        {
            lv_style_set_bitmap_mask_src(_lv_style, v);

            return *this;
        }

        style &style::set_rotary_sensitivity(uint32_t v)
        {
            lv_style_set_rotary_sensitivity(_lv_style, v);

            return *this;
        }

        style &style::set_flex_flow(object::flex_flow v)
        {
            lv_style_set_flex_flow(_lv_style, static_cast<lv_flex_flow_t>(v));

            return *this;
        }

        style &style::set_flex_main_place(object::flex_alignment v)
        {
            lv_style_set_flex_main_place(_lv_style, static_cast<lv_flex_align_t>(v));

            return *this;
        }

        style &style::set_flex_cross_place(object::flex_alignment v)
        {
            lv_style_set_flex_cross_place(_lv_style, static_cast<lv_flex_align_t>(v));

            return *this;
        }

        style &style::set_flex_track_place(object::flex_alignment v)
        {
            lv_style_set_flex_track_place(_lv_style, static_cast<lv_flex_align_t>(v));

            return *this;
        }

        style &style::set_flex_grow(uint8_t v)
        {
            lv_style_set_flex_grow(_lv_style, v);

            return *this;
        }

        style &style::set_grid_column_dsc_array(const int32_t *v)
        {
            lv_style_set_grid_column_dsc_array(_lv_style, v);

            return *this;
        }

        style &style::set_grid_column_align(object::grid_alignment v)
        {
            lv_style_set_grid_column_align(_lv_style, static_cast<lv_grid_align_t>(v));

            return *this;
        }

        style &style::set_grid_row_dsc_array(const int32_t *v)
        {
            lv_style_set_grid_row_dsc_array(_lv_style, v);

            return *this;
        }

        style &style::set_grid_row_align(object::grid_alignment v)
        {
            lv_style_set_grid_row_align(_lv_style, static_cast<lv_grid_align_t>(v));

            return *this;
        }

        style &style::set_grid_cell_column_pos(int32_t v)
        {
            lv_style_set_grid_cell_column_pos(_lv_style, v);

            return *this;
        }

        style &style::set_grid_cell_x_align(object::grid_alignment v)
        {
            lv_style_set_grid_cell_x_align(_lv_style, static_cast<lv_grid_align_t>(v));

            return *this;
        }

        style &style::set_grid_cell_column_span(int32_t v)
        {
            lv_style_set_grid_cell_column_span(_lv_style, v);

            return *this;
        }

        style &style::set_grid_cell_row_pos(int32_t v)
        {
            lv_style_set_grid_cell_row_pos(_lv_style, v);

            return *this;
        }

        style &style::set_grid_cell_y_align(object::grid_alignment v)
        {
            lv_style_set_grid_cell_y_align(_lv_style, static_cast<lv_grid_align_t>(v));

            return *this;
        }

        style &style::set_grid_cell_row_span(int32_t v)
        {
            lv_style_set_grid_cell_row_span(_lv_style, v);

            return *this;
        }

        void style::report_change()
        {
            lv_obj_report_style_change(_lv_style);
        }

        void *style::lv_style()
        {
            return mp_style;
        }
    };
}