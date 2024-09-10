#include "ui/lvgl/style.h"

#define lv_style static_cast<lv_style_t *>(mp_style)
#define lv_color(c)         \
    lv_color_t              \
    {                       \
        .blue = c.blue(),   \
        .green = c.green(), \
        .red = c.red()      \
    }

#include <lvgl.h>

namespace ui
{
    namespace lvgl
    {
        style::style() : mp_style(lv_malloc(sizeof(lv_style_t)))
        {
            lv_style_init(lv_style);
        }

        style::~style()
        {
            lv_style_reset(lv_style);

            lv_free(mp_style);
        }

        style &style::set_width(int32_t v)
        {
            lv_style_set_width(lv_style, v);

            return *this;
        }

        style &style::set_min_width(int32_t v)
        {
            lv_style_set_min_width(lv_style, v);

            return *this;
        }

        style &style::set_max_width(int32_t v)
        {
            lv_style_set_max_width(lv_style, v);

            return *this;
        }

        style &style::set_height(int32_t v)
        {
            lv_style_set_height(lv_style, v);

            return *this;
        }

        style &style::set_min_height(int32_t v)
        {
            lv_style_set_min_height(lv_style, v);

            return *this;
        }

        style &style::set_max_height(int32_t v)
        {
            lv_style_set_max_height(lv_style, v);

            return *this;
        }

        style &style::set_length(int32_t v)
        {
            lv_style_set_length(lv_style, v);

            return *this;
        }

        style &style::set_x(int32_t v)
        {
            lv_style_set_x(lv_style, v);

            return *this;
        }

        style &style::set_y(int32_t v)
        {
            lv_style_set_y(lv_style, v);

            return *this;
        }

        style &style::set_align(object::alignment v)
        {
            lv_style_set_align(lv_style, static_cast<lv_align_t>(v));

            return *this;
        }

        style &style::set_transform_width(int32_t v)
        {
            lv_style_set_transform_width(lv_style, v);

            return *this;
        }

        style &style::set_transform_height(int32_t v)
        {
            lv_style_set_transform_height(lv_style, v);

            return *this;
        }

        style &style::set_translate_x(int32_t v)
        {
            lv_style_set_translate_x(lv_style, v);

            return *this;
        }

        style &style::set_translate_y(int32_t v)
        {
            lv_style_set_translate_y(lv_style, v);

            return *this;
        }

        style &style::set_transform_scale_x(int32_t v)
        {
            lv_style_set_transform_scale_x(lv_style, v);

            return *this;
        }

        style &style::set_transform_scale_y(int32_t v)
        {
            lv_style_set_transform_scale_y(lv_style, v);

            return *this;
        }

        style &style::set_transform_rotation(int32_t v)
        {
            lv_style_set_transform_rotation(lv_style, v);

            return *this;
        }

        style &style::set_transform_pivot_x(int32_t v)
        {
            lv_style_set_transform_pivot_x(lv_style, v);

            return *this;
        }

        style &style::set_transform_pivot_y(int32_t v)
        {
            lv_style_set_transform_pivot_y(lv_style, v);

            return *this;
        }

        style &style::set_transform_skew_x(int32_t v)
        {
            lv_style_set_transform_skew_x(lv_style, v);

            return *this;
        }

        style &style::set_transform_skew_y(int32_t v)
        {
            lv_style_set_transform_skew_y(lv_style, v);

            return *this;
        }

        style &style::set_pad_top(int32_t v)
        {
            lv_style_set_pad_top(lv_style, v);

            return *this;
        }

        style &style::set_pad_bottom(int32_t v)
        {
            lv_style_set_pad_bottom(lv_style, v);

            return *this;
        }

        style &style::set_pad_left(int32_t v)
        {
            lv_style_set_pad_left(lv_style, v);

            return *this;
        }

        style &style::set_pad_right(int32_t v)
        {
            lv_style_set_pad_right(lv_style, v);

            return *this;
        }

        style &style::set_pad_row(int32_t v)
        {
            lv_style_set_pad_row(lv_style, v);

            return *this;
        }

        style &style::set_pad_column(int32_t v)
        {
            lv_style_set_pad_column(lv_style, v);

            return *this;
        }

        style &style::set_margin_top(int32_t v)
        {
            lv_style_set_margin_top(lv_style, v);

            return *this;
        }

        style &style::set_margin_bottom(int32_t v)
        {
            lv_style_set_margin_bottom(lv_style, v);

            return *this;
        }

        style &style::set_margin_left(int32_t v)
        {
            lv_style_set_margin_left(lv_style, v);

            return *this;
        }

        style &style::set_margin_right(int32_t v)
        {
            lv_style_set_margin_right(lv_style, v);

            return *this;
        }

        style &style::set_bg_color(color v)
        {
            lv_style_set_bg_color(lv_style, lv_color(v));

            return *this;
        }

        style &style::set_bg_opa(uint8_t v)
        {
            lv_style_set_bg_opa(lv_style, v);

            return *this;
        }

        style &style::set_bg_grad_color(color v)
        {
            lv_style_set_bg_grad_color(lv_style, lv_color(v));

            return *this;
        }

        style &style::set_bg_grad_dir(gradiant_direction v)
        {
            lv_style_set_bg_grad_dir(lv_style, static_cast<lv_grad_dir_t>(v));

            return *this;
        }

        style &style::set_bg_main_stop(int32_t v)
        {
            lv_style_set_bg_main_stop(lv_style, v);

            return *this;
        }

        style &style::set_bg_grad_stop(int32_t v)
        {
            lv_style_set_bg_grad_stop(lv_style, v);

            return *this;
        }

        style &style::set_bg_main_opa(uint8_t v)
        {
            lv_style_set_bg_main_opa(lv_style, v);

            return *this;
        }

        style &style::set_bg_grad_opa(uint8_t v)
        {
            lv_style_set_bg_grad_opa(lv_style, v);

            return *this;
        }

        style &style::set_bg_image_src(const void *v)
        {
            lv_style_set_bg_image_src(lv_style, v);

            return *this;
        }

        style &style::set_bg_image_opa(uint8_t v)
        {
            lv_style_set_bg_image_opa(lv_style, v);

            return *this;
        }

        style &style::set_bg_image_recolor(color v)
        {
            lv_style_set_bg_image_recolor(lv_style, lv_color(v));

            return *this;
        }

        style &style::set_bg_image_recolor_opa(uint8_t v)
        {
            lv_style_set_bg_image_recolor_opa(lv_style, v);

            return *this;
        }

        style &style::set_bg_image_tiled(bool v)
        {
            lv_style_set_bg_image_tiled(lv_style, v);

            return *this;
        }

        style &style::set_border_color(color v)
        {
            lv_style_set_border_color(lv_style, lv_color(v));

            return *this;
        }

        style &style::set_border_opa(uint8_t v)
        {
            lv_style_set_border_opa(lv_style, v);

            return *this;
        }

        style &style::set_border_width(int32_t v)
        {
            lv_style_set_border_width(lv_style, v);

            return *this;
        }

        style &style::set_border_side(border_side v)
        {
            lv_style_set_border_side(lv_style, static_cast<lv_border_side_t>(v));

            return *this;
        }

        style &style::set_border_post(bool v)
        {
            lv_style_set_border_post(lv_style, v);

            return *this;
        }

        style &style::set_outline_width(int32_t v)
        {
            lv_style_set_outline_width(lv_style, v);

            return *this;
        }

        style &style::set_outline_color(color v)
        {
            lv_style_set_outline_color(lv_style, lv_color(v));

            return *this;
        }

        style &style::set_outline_opa(uint8_t v)
        {
            lv_style_set_outline_opa(lv_style, v);

            return *this;
        }

        style &style::set_outline_pad(int32_t v)
        {
            lv_style_set_outline_pad(lv_style, v);

            return *this;
        }

        style &style::set_shadow_width(int32_t v)
        {
            lv_style_set_shadow_width(lv_style, v);

            return *this;
        }

        style &style::set_shadow_offset_x(int32_t v)
        {
            lv_style_set_shadow_offset_x(lv_style, v);

            return *this;
        }

        style &style::set_shadow_offset_y(int32_t v)
        {
            lv_style_set_shadow_offset_y(lv_style, v);

            return *this;
        }

        style &style::set_shadow_spread(int32_t v)
        {
            lv_style_set_shadow_spread(lv_style, v);

            return *this;
        }

        style &style::set_shadow_color(color v)
        {
            lv_style_set_shadow_color(lv_style, lv_color(v));

            return *this;
        }

        style &style::set_shadow_opa(uint8_t v)
        {
            lv_style_set_shadow_opa(lv_style, v);

            return *this;
        }

        style &style::set_image_opa(uint8_t v)
        {
            lv_style_set_image_opa(lv_style, v);

            return *this;
        }

        style &style::set_image_recolor(color v)
        {
            lv_style_set_image_recolor(lv_style, lv_color(v));

            return *this;
        }

        style &style::set_image_recolor_opa(uint8_t v)
        {
            lv_style_set_image_recolor_opa(lv_style, v);

            return *this;
        }

        style &style::set_line_width(int32_t v)
        {
            lv_style_set_line_width(lv_style, v);

            return *this;
        }

        style &style::set_line_dash_width(int32_t v)
        {
            lv_style_set_line_dash_width(lv_style, v);

            return *this;
        }

        style &style::set_line_dash_gap(int32_t v)
        {
            lv_style_set_line_dash_gap(lv_style, v);

            return *this;
        }

        style &style::set_line_rounded(bool v)
        {
            lv_style_set_line_rounded(lv_style, v);

            return *this;
        }

        style &style::set_line_color(color v)
        {
            lv_style_set_line_color(lv_style, lv_color(v));

            return *this;
        }

        style &style::set_line_opa(uint8_t v)
        {
            lv_style_set_line_opa(lv_style, v);

            return *this;
        }

        style &style::set_arc_width(int32_t v)
        {
            lv_style_set_arc_width(lv_style, v);

            return *this;
        }

        style &style::set_arc_rounded(bool v)
        {
            lv_style_set_arc_rounded(lv_style, v);

            return *this;
        }

        style &style::set_arc_color(color v)
        {
            lv_style_set_arc_color(lv_style, lv_color(v));

            return *this;
        }

        style &style::set_arc_opa(uint8_t v)
        {
            lv_style_set_arc_opa(lv_style, v);

            return *this;
        }

        style &style::set_arc_image_src(const void *v)
        {
            lv_style_set_arc_image_src(lv_style, v);

            return *this;
        }

        style &style::set_text_color(color v)
        {
            lv_style_set_text_color(lv_style, lv_color(v));

            return *this;
        }

        style &style::set_text_opa(uint8_t v)
        {
            lv_style_set_text_opa(lv_style, v);

            return *this;
        }

        style &style::set_text_font(const font &v)
        {
            lv_style_set_text_font(lv_style, v.lv_font());

            return *this;
        }

        style &style::set_text_letter_space(int32_t v)
        {
            lv_style_set_text_letter_space(lv_style, v);

            return *this;
        }

        style &style::set_text_line_space(int32_t v)
        {
            lv_style_set_text_line_space(lv_style, v);

            return *this;
        }

        style &style::set_text_decor(text_decor v)
        {
            lv_style_set_text_decor(lv_style, static_cast<lv_text_decor_t>(v));

            return *this;
        }

        style &style::set_text_align(text_alignment v)
        {
            lv_style_set_text_align(lv_style, static_cast<lv_text_align_t>(v));

            return *this;
        }

        style &style::set_radius(int32_t v)
        {
            lv_style_set_radius(lv_style, v);

            return *this;
        }

        style &style::set_clip_corner(bool v)
        {
            lv_style_set_clip_corner(lv_style, v);

            return *this;
        }

        style &style::set_opa(uint8_t v)
        {
            lv_style_set_opa(lv_style, v);

            return *this;
        }

        style &style::set_opa_layered(uint8_t v)
        {
            lv_style_set_opa_layered(lv_style, v);

            return *this;
        }

        style &style::set_color_filter_opa(uint8_t v)
        {
            lv_style_set_color_filter_opa(lv_style, v);

            return *this;
        }

        style &style::set_anim(const animation &v)
        {
            lv_style_set_anim(lv_style, v.lv_animation());

            return *this;
        }

        style &style::set_anim_duration(uint32_t v)
        {
            lv_style_set_anim_duration(lv_style, v);

            return *this;
        }

        style &style::set_blend_mode(blend_mode v)
        {
            lv_style_set_blend_mode(lv_style, static_cast<lv_blend_mode_t>(v));

            return *this;
        }

        style &style::set_layout(uint16_t v)
        {
            lv_style_set_layout(lv_style, v);

            return *this;
        }

        style &style::set_base_dir(base_direction v)
        {
            lv_style_set_base_dir(lv_style, static_cast<lv_base_dir_t>(v));

            return *this;
        }

        style &style::set_bitmap_mask_src(const void *v)
        {
            lv_style_set_bitmap_mask_src(lv_style, v);

            return *this;
        }

        style &style::set_rotary_sensitivity(uint32_t v)
        {
            lv_style_set_rotary_sensitivity(lv_style, v);

            return *this;
        }

        style &style::set_flex_flow(object::flex_flow v)
        {
            lv_style_set_flex_flow(lv_style, static_cast<lv_flex_flow_t>(v));

            return *this;
        }

        style &style::set_flex_main_place(object::flex_alignment v)
        {
            lv_style_set_flex_main_place(lv_style, static_cast<lv_flex_align_t>(v));

            return *this;
        }

        style &style::set_flex_cross_place(object::flex_alignment v)
        {
            lv_style_set_flex_cross_place(lv_style, static_cast<lv_flex_align_t>(v));

            return *this;
        }

        style &style::set_flex_track_place(object::flex_alignment v)
        {
            lv_style_set_flex_track_place(lv_style, static_cast<lv_flex_align_t>(v));

            return *this;
        }

        style &style::set_flex_grow(uint8_t v)
        {
            lv_style_set_flex_grow(lv_style, v);

            return *this;
        }

        style &style::set_grid_column_dsc_array(const int32_t *v)
        {
            lv_style_set_grid_column_dsc_array(lv_style, v);

            return *this;
        }

        style &style::set_grid_column_align(object::grid_alignment v)
        {
            lv_style_set_grid_column_align(lv_style, static_cast<lv_grid_align_t>(v));

            return *this;
        }

        style &style::set_grid_row_dsc_array(const int32_t *v)
        {
            lv_style_set_grid_row_dsc_array(lv_style, v);

            return *this;
        }

        style &style::set_grid_row_align(object::grid_alignment v)
        {
            lv_style_set_grid_row_align(lv_style, static_cast<lv_grid_align_t>(v));

            return *this;
        }

        style &style::set_grid_cell_column_pos(int32_t v)
        {
            lv_style_set_grid_cell_column_pos(lv_style, v);

            return *this;
        }

        style &style::set_grid_cell_x_align(object::grid_alignment v)
        {
            lv_style_set_grid_cell_x_align(lv_style, static_cast<lv_grid_align_t>(v));

            return *this;
        }

        style &style::set_grid_cell_column_span(int32_t v)
        {
            lv_style_set_grid_cell_column_span(lv_style, v);

            return *this;
        }

        style &style::set_grid_cell_row_pos(int32_t v)
        {
            lv_style_set_grid_cell_row_pos(lv_style, v);

            return *this;
        }

        style &style::set_grid_cell_y_align(object::grid_alignment v)
        {
            lv_style_set_grid_cell_y_align(lv_style, static_cast<lv_grid_align_t>(v));

            return *this;
        }

        style &style::set_grid_cell_row_span(int32_t v)
        {
            lv_style_set_grid_cell_row_span(lv_style, v);

            return *this;
        }
    };
}