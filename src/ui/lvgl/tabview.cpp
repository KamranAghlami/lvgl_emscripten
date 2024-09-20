#include "ui/lvgl/tabview.h"

#include <lvgl.h>

namespace ui
{
    namespace lvgl
    {
        tabview::tab_descriptor_base::tab_descriptor_base(object &tab_bar)
            : m_button(lv_obj_get_child(tab_bar.lv_object(), -1)),
              m_label(lv_obj_get_child(m_button.lv_object(), -1))
        {
        }

        tabview::tabview(object &parent)
            : object(lv_tabview_create(parent.lv_object())),
              m_tab_bar(lv_tabview_get_tab_bar(lv_object())),
              m_content(lv_tabview_get_content(lv_object()))
        {
        }

        tabview &tabview::rename_tab(uint32_t index, const char *new_name)
        {
            lv_tabview_rename_tab(lv_object(), index, new_name);

            return *this;
        }

        tabview &tabview::set_tab_active(uint32_t index, bool animation_enable)
        {
            lv_tabview_set_active(lv_object(), index, static_cast<lv_anim_enable_t>(animation_enable));

            return *this;
        }

        tabview &tabview::set_tab_bar_position(direction d)
        {
            lv_tabview_set_tab_bar_position(lv_object(), static_cast<lv_dir_t>(d));

            return *this;
        }

        tabview &tabview::set_tab_bar_size(int32_t size)
        {
            lv_tabview_set_tab_bar_size(lv_object(), size);

            return *this;
        }

        uint32_t tabview::get_tab_count()
        {
            return lv_tabview_get_tab_count(lv_object());
        }

        uint32_t tabview::get_tab_active()
        {
            return lv_tabview_get_tab_active(lv_object());
        }

        object &tabview::get_content()
        {
            return m_content;
        }

        object &tabview::get_tab_bar()
        {
            return m_tab_bar;
        }
    }
}