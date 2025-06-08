#include "ui/widgets/thingy.h"

#include "driver/filesystem.h"
#include "src/core/lv_obj_class_private.h"
#include "src/core/lv_obj_private.h"
#include "src/misc/lv_text_private.h"

namespace ui
{
    namespace widgets
    {
        namespace thingy
        {
            struct thingy
            {
                lv_obj_t base;

                lv_style_t style;

                lv_obj_t *label;
                lv_obj_t *image;
            };

            static void recolor(lv_obj_t *obj)
            {
                auto self = reinterpret_cast<thingy *>(obj);

                const lv_color_t c = {
                    .blue = static_cast<uint8_t>(lv_rand(0, 0xff)),
                    .green = static_cast<uint8_t>(lv_rand(0, 0xff)),
                    .red = static_cast<uint8_t>(lv_rand(0, 0xff)),
                };

                lv_style_set_bg_color(&self->style, c);

                const lv_color_t c_neg = {
                    static_cast<uint8_t>(0xff - c.blue),
                    static_cast<uint8_t>(0xff - c.green),
                    static_cast<uint8_t>(0xff - c.red),
                };

                lv_style_set_text_color(&self->style, c_neg);

                lv_obj_report_style_change(&self->style);
            }

            static void constructor(const lv_obj_class_t *class_p, lv_obj_t *obj)
            {
                auto self = reinterpret_cast<thingy *>(obj);

                lv_style_init(&self->style);

                lv_style_set_bg_opa(&self->style, LV_OPA_100);

                lv_obj_add_style(obj, &self->style, LV_PART_MAIN | LV_STATE_DEFAULT);

                self->image = lv_image_create(obj);

                auto on_fetch = [self](const driver::memory::string &path)
                {
                    lv_image_set_src(self->image, path.c_str());
                };

                driver::filesystem::get().fetch("image/icon.png", on_fetch);

                lv_image_set_scale(self->image, 128);
                lv_obj_set_size(self->image, LV_PCT(100), LV_PCT(100));
                lv_obj_align(self->image, LV_ALIGN_CENTER, 0, 0);

                self->label = lv_label_create(obj);

                lv_obj_align(self->label, LV_ALIGN_CENTER, 0, 0);

                auto on_pressed = [](lv_event_t *e)
                {
                    auto obj = lv_event_get_target_obj(e);

                    recolor(obj);
                };

                lv_obj_add_event_cb(obj, on_pressed, LV_EVENT_PRESSED, nullptr);

                recolor(obj);
            }

            static void destructor(const lv_obj_class_t *class_p, lv_obj_t *obj)
            {
                auto self = reinterpret_cast<thingy *>(obj);

                lv_style_reset(&self->style);
            }

            const lv_obj_class_t thingy_class = {
                .base_class = &lv_obj_class,
                .constructor_cb = constructor,
                .destructor_cb = destructor,
                .name = "ui::widgets::thingy",
                .width_def = LV_DPI_DEF,
                .height_def = LV_DPI_DEF,
                .instance_size = sizeof(thingy),
            };

            lv_obj_t *create(lv_obj_t *parent)
            {
                lv_obj_t *obj = lv_obj_class_create_obj(&thingy_class, parent);

                lv_obj_class_init_obj(obj);

                return obj;
            }

            void set_text_fmt(lv_obj_t *obj, const char *fmt, ...)
            {
                auto self = reinterpret_cast<thingy *>(obj);

                va_list args;

                va_start(args, fmt);
                auto text = lv_text_set_text_vfmt(fmt, args);
                va_end(args);

                lv_label_set_text(self->label, text);

                lv_free(text);
            }
        }
    }
}