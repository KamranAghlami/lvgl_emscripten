#pragma once

#include <vector>
#include <memory>

#include <lvgl.h>

#include "ui/lvgl/screen.h"

namespace ui
{
    namespace screens
    {
        // TODO:
        // groups styles selectors timers animations labels buttons images fonts ...

        class main : public lvgl::screen
        {
        public:
            main()
            {
                draw();
            }

            ~main()
            {
                lv_free(m_row_dsc);
                lv_free(m_col_dsc);
            }

        private:
            void draw()
            {
                m_children.clear();

                if (m_row_dsc)
                    lv_free(m_row_dsc);

                if (m_col_dsc)
                    lv_free(m_col_dsc);

                m_col_dsc = static_cast<int32_t *>(lv_malloc((m_columns + 1) * sizeof(int32_t)));
                m_row_dsc = static_cast<int32_t *>(lv_malloc((m_rows + 1) * sizeof(int32_t)));

                std::fill(m_col_dsc, m_col_dsc + m_columns, GRID_FR(1));
                std::fill(m_row_dsc, m_row_dsc + m_rows, GRID_FR(1));

                m_col_dsc[m_columns] = GRID_TEMPLATE_LAST();
                m_row_dsc[m_rows] = GRID_TEMPLATE_LAST();

                set_layout(layout::GRID);
                set_grid_dsc_array(m_col_dsc, m_row_dsc);
                set_grid_align(grid_alignment::CENTER, grid_alignment::CENTER);

                for (int32_t i = 0; i < m_rows; i++)
                    for (int32_t j = 0; j < m_columns; j++)
                    {
                        m_children.push_back(std::make_unique<object>(this));

                        auto on_pressed = [this](lvgl::event &e)
                        {
                            lv_obj_set_style_bg_color(static_cast<lv_obj_t *>(e.m_current_target.lv_object()),
                                                      lv_color_make(lv_rand(0, 0xFF),
                                                                    lv_rand(0, 0xFF),
                                                                    lv_rand(0, 0xFF)),
                                                      LV_PART_MAIN | LV_STATE_DEFAULT);
                        };

                        object &rect = *m_children.back();

                        rect.set_grid_cell(
                                grid_alignment::STRETCH, j, 1,
                                grid_alignment::STRETCH, i, 1)
                            .add_flag(flag::CLICKABLE | flag::EVENT_BUBBLE)
                            .add_event_callback(lvgl::event::code::PRESSED, on_pressed);
                    }
            }

            std::vector<std::unique_ptr<object>> m_children;
            size_t m_columns = 10;
            size_t m_rows = 10;
            int32_t *m_col_dsc = nullptr;
            int32_t *m_row_dsc = nullptr;
        };
    }
}
