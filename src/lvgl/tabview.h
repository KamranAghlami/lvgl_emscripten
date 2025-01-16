#pragma once

#include <memory>
#include <vector>

#include "driver/memory.h"
#include "lvgl/object.h"
#include "lvgl/button.h"
#include "lvgl/label.h"

extern "C"
{
    lv_obj_t *lv_tabview_add_tab(lv_obj_t *, const char *);
}

namespace lvgl
{
    class tabview : public object
    {
    public:
        class tab : public object
        {
        public:
            tab(lv_obj_t *lv_obj, tabview &tv);

            virtual ~tab() = default;

            button &get_button()
            {
                return m_button;
            }

            label &get_label()
            {
                return m_label;
            }

            virtual lvgl::group *get_tab_group() = 0;

        protected:
            void focus_tab_bar()
            {
                m_tabview.focus_tab_bar();
            }

        private:
            button m_button;
            label m_label;
            tabview &m_tabview;
        };

        tabview(object &parent);

        virtual ~tabview() = default;

        template <typename T = object>
        tab &add_tab(const char *name);

        tabview &rename_tab(uint32_t index, const char *new_name);
        tabview &set_tab_active(uint32_t index, bool animation_enable = false);
        tabview &set_tab_bar_position(direction d);
        tabview &set_tab_bar_size(int32_t size);

        uint32_t get_tab_count();
        uint32_t get_tab_active();

        object &get_content();
        object &get_tab_bar();

    protected:
        virtual void focus_tab_bar() = 0;

        driver::memory::vector<driver::memory::unique_ptr<tab>> m_tabs;

    private:
        object m_tab_bar;
        object m_content;
    };

    template <typename T>
    tabview::tab &tabview::add_tab(const char *name)
    {
        static_assert(std::is_base_of_v<tabview::tab, T>, "T must be derived from lvgl::tabview::tab");

        m_tabs.push_back(
            driver::memory::make_unique<T>(lv_tabview_add_tab(lv_object(), name), *this));

        return *m_tabs.back();
    }
}
