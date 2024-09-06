#pragma once

#include "ui/lvgl/object.h"

extern "C"
{
    void lv_label_set_text_fmt(lv_obj_t *, const char *, ...);
}

namespace ui
{
    namespace lvgl
    {

        class label : public object
        {
        public:
            enum class long_mode
            {
                WRAP,
                DOT,
                SCROLL,
                SCROLL_CIRCULAR,
                CLIP,
            };

            label(object &parent);
            ~label();

            label &set_text(const char *text);

            template <typename... Args>
            label &set_text_fmt(const char *fmt, Args &&...args);

            label &set_text_static(const char *text);
            label &set_long_mode(long_mode mode);
            label &set_text_selection_start(uint32_t index);
            label &set_text_selection_end(uint32_t index);

            char *get_text();
            long_mode get_long_mode();
            uint32_t get_text_selection_start();
            uint32_t get_text_selection_end();

            label &insert_text(uint32_t position, const char *text);
            label &cut_text(uint32_t position, uint32_t count);
        };

        template <typename... Args>
        label &label::set_text_fmt(const char *fmt, Args &&...args)
        {
            lv_label_set_text_fmt(lv_object(), fmt, std::forward<Args>(args)...);

            return *this;
        }
    }
}
