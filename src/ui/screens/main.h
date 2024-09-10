#pragma once

#include <vector>
#include <memory>

#include <lvgl.h>

#include "ui/lvgl/lvgl.h"
#include "ui/widgets/widget_thingy.h"

namespace ui
{
    namespace screens
    {
        // TODO:
        // styles animations fonts ...

        class main : public lvgl::screen
        {
        public:
            main()
            {
                m_group.add_object(*this);

                auto on_load = [this](lvgl::event &e)
                {
                    m_group.activate();
                };

                add_event_callback(lvgl::event::code::SCREEN_LOADED, on_load);

                auto on_key = [this](lvgl::event &e)
                {
                    switch (static_cast<lvgl::group::key_code>(e.get_key()))
                    {
                    case lvgl::group::key_code::UP:
                    case lvgl::group::key_code::RIGHT:
                        if (m_columns < 32 && m_rows < 32)
                        {
                            m_columns *= 2;
                            m_rows *= 2;

                            draw();
                        }

                        break;

                    case lvgl::group::key_code::DOWN:
                    case lvgl::group::key_code::LEFT:
                        if (m_columns > 1 && m_rows > 1)
                        {
                            m_columns /= 2;
                            m_rows /= 2;

                            draw();
                        }

                        break;

                    default:
                        break;
                    }
                };

                add_event_callback(lvgl::event::code::KEY, on_key);

                remove_flag(flag::CLICKABLE);

                draw();
            }

            ~main()
            {
                if (m_row_dsc)
                    lv_free(m_row_dsc);

                if (m_col_dsc)
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
                        m_children.push_back(std::make_unique<widget_thingy>(*this));

                        auto &lt = static_cast<widget_thingy &>(*m_children.back());

                        lt.set_text_fmt("%u", i * m_rows + j)
                            .set_grid_cell(
                                grid_alignment::STRETCH, j, 1,
                                grid_alignment::STRETCH, i, 1)
                            .add_flag(flag::CLICKABLE | flag::EVENT_BUBBLE);
                    }
            }

            lvgl::group m_group;
            std::vector<std::unique_ptr<object>> m_children;
            size_t m_columns = 4;
            size_t m_rows = 4;
            int32_t *m_col_dsc = nullptr;
            int32_t *m_row_dsc = nullptr;
        };
    }
}
