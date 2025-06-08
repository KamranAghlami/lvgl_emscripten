#include "ui/screens/main.h"

#include <algorithm>

#include "application/application.h"
#include "src/core/lv_obj_class_private.h"
#include "src/core/lv_obj_private.h"
#include "ui/widgets/thingy.h"

namespace ui
{
    namespace screens
    {
        namespace main
        {
            struct main
            {
                lv_obj_t base;

                lv_group_t *group;

                size_t columns;
                size_t rows;
                int32_t *col_dsc;
                int32_t *row_dsc;
            };

            static void draw(lv_obj_t *obj)
            {
                auto self = reinterpret_cast<main *>(obj);

                lv_obj_clean(obj);

                if (self->row_dsc)
                    lv_free(self->row_dsc);

                if (self->col_dsc)
                    lv_free(self->col_dsc);

                self->col_dsc = static_cast<int32_t *>(lv_malloc((self->columns + 1) * sizeof(int32_t)));
                self->row_dsc = static_cast<int32_t *>(lv_malloc((self->rows + 1) * sizeof(int32_t)));

                std::fill(self->col_dsc, self->col_dsc + self->columns, LV_GRID_FR(1));
                std::fill(self->row_dsc, self->row_dsc + self->rows, LV_GRID_FR(1));

                self->col_dsc[self->columns] = LV_GRID_TEMPLATE_LAST;
                self->row_dsc[self->rows] = LV_GRID_TEMPLATE_LAST;

                lv_obj_set_layout(obj, LV_LAYOUT_GRID);
                lv_obj_set_grid_dsc_array(obj, self->col_dsc, self->row_dsc);
                lv_obj_set_grid_align(obj, LV_GRID_ALIGN_CENTER, LV_GRID_ALIGN_CENTER);

                for (int32_t i = 0; i < self->rows; i++)
                    for (int32_t j = 0; j < self->columns; j++)
                    {
                        auto child = ui::widgets::thingy::create(obj);

                        ui::widgets::thingy::set_text_fmt(child, "%u", i * self->rows + j);

                        lv_obj_set_grid_cell(child,
                                             LV_GRID_ALIGN_STRETCH, j, 1,
                                             LV_GRID_ALIGN_STRETCH, i, 1);

                        lv_obj_add_flag(child, static_cast<lv_obj_flag_t>(LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE));
                    }
            }

            static void constructor(const lv_obj_class_t *class_p, lv_obj_t *obj)
            {
                auto self = reinterpret_cast<main *>(obj);

                self->group = lv_group_create();

                lv_group_add_obj(self->group, obj);

                auto on_load = [](lv_event_t *e)
                {
                    auto obj = lv_event_get_target_obj(e);
                    auto self = reinterpret_cast<main *>(obj);

                    application::get()->set_active_group(self->group);
                };

                lv_obj_add_event_cb(obj, on_load, LV_EVENT_SCREEN_LOADED, nullptr);

                auto on_key = [](lv_event_t *e)
                {
                    auto obj = lv_event_get_target_obj(e);
                    auto self = reinterpret_cast<main *>(obj);

                    switch (static_cast<lv_key_t>(lv_event_get_key(e)))
                    {
                    case LV_KEY_UP:
                    case LV_KEY_RIGHT:
                        if (self->columns < 32 && self->rows < 32)
                        {
                            self->columns *= 2;
                            self->rows *= 2;

                            draw(obj);
                        }

                        break;

                    case LV_KEY_DOWN:
                    case LV_KEY_LEFT:
                        if (self->columns > 1 && self->rows > 1)
                        {
                            self->columns /= 2;
                            self->rows /= 2;

                            draw(obj);
                        }

                        break;

                    default:
                        break;
                    }
                };

                lv_obj_add_event_cb(obj, on_key, LV_EVENT_KEY, nullptr);

                lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);

                self->columns = 4;
                self->rows = 4;

                draw(obj);
            }

            static void destructor(const lv_obj_class_t *class_p, lv_obj_t *obj)
            {
                auto self = reinterpret_cast<main *>(obj);

                if (self->row_dsc)
                    lv_free(self->row_dsc);

                if (self->col_dsc)
                    lv_free(self->col_dsc);

                lv_group_delete(self->group);
            }

            const lv_obj_class_t main_class = {
                .base_class = &lv_obj_class,
                .constructor_cb = constructor,
                .destructor_cb = destructor,
                .name = "ui::screens::main",
                .width_def = LV_PCT(100),
                .height_def = LV_PCT(100),
                .instance_size = sizeof(main),
            };

            lv_obj_t *create()
            {
                lv_obj_t *obj = lv_obj_class_create_obj(&main_class, NULL);

                lv_obj_class_init_obj(obj);

                return obj;
            }
        }
    }
}