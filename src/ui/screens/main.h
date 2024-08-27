#pragma once

#include <vector>
#include <memory>

#include "ui/lvgl/screen.h"

namespace ui
{
    namespace screens
    {
        // TODO:
        // events parent/child getters? groups styles selectors timers animations labels buttons images fonts ...

        class main : public lvgl::screen
        {
        public:
            main()
            {
                auto on_resize = [this](event &e)
                {
                    draw();
                };

                add_event_callback(event::code::SIZE_CHANGED, on_resize);

                draw();
            }

        private:
            void draw()
            {
                m_children.clear();

                const float w = width() / 5.75f;
                const float h = height() / 5.75f;
                const int32_t sw = w / 8;
                const int32_t sh = h / 8;

                for (int32_t y = 0; y < 5; y++)
                    for (int32_t x = 0; x < 5; x++)
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

                        rect.set_x(sw + (x * (w + sw)))
                            .set_y(sh + (y * (h + sh)))
                            .set_width(w)
                            .set_height(h)
                            .add_flag(flag::CLICKABLE)
                            .add_event_callback(event::code::PRESSED, on_pressed);
                    }
            }

            std::vector<std::unique_ptr<object>> m_children;
        };
    }
}
