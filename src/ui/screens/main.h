#pragma once

#include <vector>
#include <memory>

#include "ui/lvgl/screen.h"

namespace ui
{
    namespace screens
    {
        // TODO:
        // grids groups styles selectors timers animations labels buttons images fonts ...

        class main : public lvgl::screen
        {
        public:
            main()
            {
                set_layout(layout::FLEX);
                set_flex_flow(flex_flow::ROW_WRAP);
                set_flex_align(flex_alignment::SPACE_EVENLY, flex_alignment::SPACE_EVENLY, flex_alignment::SPACE_EVENLY);

                for (int32_t x = 0; x < 400; x++)
                {
                    m_children.push_back(std::make_unique<object>(this));

                    auto on_pressed = [this](event &e)
                    {
                        lv_obj_set_style_bg_color(static_cast<lv_obj_t *>(e.m_current_target.lv_object()),
                                                  lv_color_make(lv_rand(0, 0xFF),
                                                                lv_rand(0, 0xFF),
                                                                lv_rand(0, 0xFF)),
                                                  LV_PART_MAIN | LV_STATE_DEFAULT);
                    };

                    object &rect = *m_children.back();

                    rect.set_width(object::PERCENTAGE(5))
                        .set_height(object::PERCENTAGE(5))
                        .add_flag(flag::CLICKABLE)
                        .add_event_callback(event::code::PRESSED, on_pressed);
                }
            }

        private:
            std::vector<std::unique_ptr<object>> m_children;
        };
    }
}
