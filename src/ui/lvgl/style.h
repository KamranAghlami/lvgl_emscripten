#pragma once

#include <cstdint>

#include "ui/lvgl/object.h"
#include "ui/lvgl/color.h"
#include "ui/lvgl/font.h"
#include "ui/lvgl/animation.h"

namespace ui
{
    namespace lvgl
    {
        class style
        {
        public:
            enum class blend_mode : uint8_t
            {
                NORMAL,
                ADDITIVE,
                SUBTRACTIVE,
                MULTIPLY,
            };

            enum class text_decor : uint8_t
            {
                NONE = 0x00,
                UNDERLINE = 0x01,
                STRIKETHROUGH = 0x02,
            };

            enum class border_side : uint8_t
            {
                NONE = 0x00,
                BOTTOM = 0x01,
                TOP = 0x02,
                LEFT = 0x04,
                RIGHT = 0x08,
                FULL = 0x0F,
                INTERNAL = 0x10,
            };

            enum class gradiant_direction : uint8_t
            {
                NONE,
                VER,
                HOR,
                LINEAR,
                RADIAL,
                CONICAL,
            };

            enum class text_alignment : uint8_t
            {
                AUTO,
                LEFT,
                CENTER,
                RIGHT,
            };

            enum class base_direction : uint8_t
            {
                LTR = 0x00,
                RTL = 0x01,
                AUTO = 0x02,

                NEUTRAL = 0x20,
                WEAK = 0x21,
            };

            style();
            ~style();

            style(const style &) = delete;
            style(style &&) = delete;
            style &operator=(const style &) = delete;
            style &operator=(style &&) = delete;

            style &set_width(int32_t v);
            style &set_min_width(int32_t v);
            style &set_max_width(int32_t v);
            style &set_height(int32_t v);
            style &set_min_height(int32_t v);
            style &set_max_height(int32_t v);
            style &set_length(int32_t v);
            style &set_x(int32_t v);
            style &set_y(int32_t v);
            style &set_align(object::alignment v);
            style &set_transform_width(int32_t v);
            style &set_transform_height(int32_t v);
            style &set_translate_x(int32_t v);
            style &set_translate_y(int32_t v);
            style &set_transform_scale_x(int32_t v);
            style &set_transform_scale_y(int32_t v);
            style &set_transform_rotation(int32_t v);
            style &set_transform_pivot_x(int32_t v);
            style &set_transform_pivot_y(int32_t v);
            style &set_transform_skew_x(int32_t v);
            style &set_transform_skew_y(int32_t v);
            style &set_pad_top(int32_t v);
            style &set_pad_bottom(int32_t v);
            style &set_pad_left(int32_t v);
            style &set_pad_right(int32_t v);
            style &set_pad_row(int32_t v);
            style &set_pad_column(int32_t v);
            style &set_pad_all(int32_t value);
            style &set_pad_hor(int32_t value);
            style &set_pad_ver(int32_t value);
            style &set_pad_gap(int32_t value);
            style &set_margin_top(int32_t v);
            style &set_margin_bottom(int32_t v);
            style &set_margin_left(int32_t v);
            style &set_margin_right(int32_t v);
            style &set_bg_color(const color &v);
            style &set_bg_opa(uint8_t v);
            style &set_bg_grad_color(const color &v);
            style &set_bg_grad_dir(gradiant_direction v);
            style &set_bg_main_stop(int32_t v);
            style &set_bg_grad_stop(int32_t v);
            style &set_bg_main_opa(uint8_t v);
            style &set_bg_grad_opa(uint8_t v);
            style &set_bg_image_src(const void *v);
            style &set_bg_image_opa(uint8_t v);
            style &set_bg_image_recolor(const color &v);
            style &set_bg_image_recolor_opa(uint8_t v);
            style &set_bg_image_tiled(bool v);
            style &set_border_color(const color &v);
            style &set_border_opa(uint8_t v);
            style &set_border_width(int32_t v);
            style &set_border_side(border_side v);
            style &set_border_post(bool v);
            style &set_outline_width(int32_t v);
            style &set_outline_color(const color &v);
            style &set_outline_opa(uint8_t v);
            style &set_outline_pad(int32_t v);
            style &set_shadow_width(int32_t v);
            style &set_shadow_offset_x(int32_t v);
            style &set_shadow_offset_y(int32_t v);
            style &set_shadow_spread(int32_t v);
            style &set_shadow_color(const color &v);
            style &set_shadow_opa(uint8_t v);
            style &set_image_opa(uint8_t v);
            style &set_image_recolor(const color &v);
            style &set_image_recolor_opa(uint8_t v);
            style &set_line_width(int32_t v);
            style &set_line_dash_width(int32_t v);
            style &set_line_dash_gap(int32_t v);
            style &set_line_rounded(bool v);
            style &set_line_color(const color &v);
            style &set_line_opa(uint8_t v);
            style &set_arc_width(int32_t v);
            style &set_arc_rounded(bool v);
            style &set_arc_color(const color &v);
            style &set_arc_opa(uint8_t v);
            style &set_arc_image_src(const void *v);
            style &set_text_color(const color &v);
            style &set_text_opa(uint8_t v);
            style &set_text_font(const font &v);
            style &set_text_letter_space(int32_t v);
            style &set_text_line_space(int32_t v);
            style &set_text_decor(text_decor v);
            style &set_text_align(text_alignment v);
            style &set_radius(int32_t v);
            style &set_clip_corner(bool v);
            style &set_opa(uint8_t v);
            style &set_opa_layered(uint8_t v);
            style &set_color_filter_opa(uint8_t v);
            style &set_anim(const animation &v);
            style &set_anim_duration(uint32_t v);
            style &set_blend_mode(blend_mode v);
            style &set_layout(uint16_t v);
            style &set_base_dir(base_direction v);
            style &set_bitmap_mask_src(const void *v);
            style &set_rotary_sensitivity(uint32_t v);
            style &set_flex_flow(object::flex_flow v);
            style &set_flex_main_place(object::flex_alignment v);
            style &set_flex_cross_place(object::flex_alignment v);
            style &set_flex_track_place(object::flex_alignment v);
            style &set_flex_grow(uint8_t v);
            style &set_grid_column_dsc_array(const int32_t *v);
            style &set_grid_column_align(object::grid_alignment v);
            style &set_grid_row_dsc_array(const int32_t *v);
            style &set_grid_row_align(object::grid_alignment v);
            style &set_grid_cell_column_pos(int32_t v);
            style &set_grid_cell_x_align(object::grid_alignment v);
            style &set_grid_cell_column_span(int32_t v);
            style &set_grid_cell_row_pos(int32_t v);
            style &set_grid_cell_y_align(object::grid_alignment v);
            style &set_grid_cell_row_span(int32_t v);

            void reset();
            void report_change();
            void *lv_style();

        private:
            void *mp_style;

            friend class object;
        };
    }
}
