#include "ui/lvgl/image.h"

#include <lvgl.h>

namespace ui
{
    namespace lvgl
    {
        image::image(object &parent) : object(lv_image_create(parent.lv_object()))
        {
        }

        image::~image()
        {
        }

        image &image::set_source(const void *source)
        {
            lv_image_set_src(lv_object(), source);

            return *this;
        }

        image &image::set_offset_x(int32_t offset_x)
        {
            lv_image_set_offset_x(lv_object(), offset_x);

            return *this;
        }

        image &image::set_offset_y(int32_t offset_y)
        {
            lv_image_set_offset_y(lv_object(), offset_y);

            return *this;
        }

        image &image::set_rotation(int32_t rotation)
        {
            lv_image_set_rotation(lv_object(), rotation);

            return *this;
        }

        image &image::set_pivot(int32_t pivot_x, int32_t pivot_y)
        {
            lv_image_set_pivot(lv_object(), pivot_x, pivot_y);

            return *this;
        }

        image &image::set_scale(uint32_t scale)
        {
            lv_image_set_rotation(lv_object(), scale);

            return *this;
        }

        image &image::set_scale_x(uint32_t scale_x)
        {
            lv_image_set_scale_x(lv_object(), scale_x);

            return *this;
        }

        image &image::set_scale_y(uint32_t scale_y)
        {
            lv_image_set_scale_y(lv_object(), scale_y);

            return *this;
        }

        image &image::set_blend_mode(style::blend_mode mode)
        {
            lv_image_set_blend_mode(lv_object(), static_cast<lv_blend_mode_t>(mode));

            return *this;
        }

        image &image::set_antialiasing(bool enable)
        {
            lv_image_set_antialias(lv_object(), enable);

            return *this;
        }

        image &image::set_inner_alignment(image_alignment alignment)
        {
            lv_image_set_inner_align(lv_object(), static_cast<lv_image_align_t>(alignment));

            return *this;
        }

        const void *image::get_source()
        {
            return lv_image_get_src(lv_object());
        }

        int32_t image::get_offset_x()
        {
            return lv_image_get_offset_x(lv_object());
        }

        int32_t image::get_offset_y()
        {
            return lv_image_get_offset_y(lv_object());
        }

        int32_t image::get_rotation()
        {
            return lv_image_get_rotation(lv_object());
        }

        int32_t image::get_scale()
        {
            return lv_image_get_scale(lv_object());
        }

        int32_t image::get_scale_x()
        {
            return lv_image_get_scale_x(lv_object());
        }

        int32_t image::get_scale_y()
        {
            return lv_image_get_scale_y(lv_object());
        }

        style::blend_mode image::get_blend_mode()
        {
            return static_cast<style::blend_mode>(lv_image_get_blend_mode(lv_object()));
        }

        bool image::get_antialiasing()
        {
            return lv_image_get_antialias(lv_object());
        }

        image::image_alignment image::get_inner_alignment()
        {
            return static_cast<image_alignment>(lv_image_get_inner_align(lv_object()));
        }
    }
}
