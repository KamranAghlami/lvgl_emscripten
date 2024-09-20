#pragma once

#include <memory>
#include <vector>

#include "ui/lvgl/object.h"
#include "ui/lvgl/button.h"
#include "ui/lvgl/label.h"

extern "C"
{
    lv_obj_t *lv_tabview_add_tab(lv_obj_t *, const char *);
}

namespace ui
{
    namespace lvgl
    {
        class tabview : public object
        {
        protected:
            template <typename T>
            class tab_descriptor;

        public:
            tabview(object &parent);

            template <typename T = object>
            tab_descriptor<T> &add_tab(const char *name);

            tabview &rename_tab(uint32_t index, const char *new_name);
            tabview &set_tab_active(uint32_t index, bool animation_enable = false);
            tabview &set_tab_bar_position(direction d);
            tabview &set_tab_bar_size(int32_t size);

            uint32_t get_tab_count();
            uint32_t get_tab_active();

            object &get_content();
            object &get_tab_bar();

        protected:
            class tab_descriptor_base
            {
            public:
                tab_descriptor_base(object &tab_bar);

                button &get_button()
                {
                    return m_button;
                }

                label &get_label()
                {
                    return m_label;
                }

                virtual ~tab_descriptor_base() = default;

            private:
                button m_button;
                label m_label;
            };

            template <typename T>
            class tab_descriptor : public tab_descriptor_base
            {
            public:
                tab_descriptor(object &tab_bar, lv_obj_t *lv_obj)
                    : tab_descriptor_base(tab_bar),
                      m_content(lv_obj)
                {
                }

                T &get_content()
                {
                    return m_content;
                }

            private:
                T m_content;
            };

        private:
            object m_tab_bar;
            object m_content;

            std::vector<std::unique_ptr<tab_descriptor_base>> m_tabs;
        };

        template <typename T>
        tabview::tab_descriptor<T> &tabview::add_tab(const char *name)
        {
            static_assert(std::is_base_of_v<object, T>, "T must be derived from lvgl::object");

            m_tabs.push_back(
                std::make_unique<tab_descriptor<T>>(
                    get_tab_bar(),
                    lv_tabview_add_tab(lv_object(), name)));

            return static_cast<tab_descriptor<T> &>(*m_tabs.back());
        }
    }
}