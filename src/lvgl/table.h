#pragma once

#include "lvgl/object.h"

extern "C"
{
    void lv_table_set_cell_value_fmt(lv_obj_t *, uint32_t, uint32_t, const char *, ...);
}

namespace lvgl
{
    class table : public object
    {
    public:
        enum class cell_control : uint8_t
        {
            MERGE_RIGHT = 1 << 0,
            TEXT_CROP = 1 << 1,
            CUSTOM_1 = 1 << 4,
            CUSTOM_2 = 1 << 5,
            CUSTOM_3 = 1 << 6,
            CUSTOM_4 = 1 << 7,
        };

        table(object &parent);

        ~table();

        table &set_cell_value(uint32_t row, uint32_t column, const char *text);

        template <typename... Args>
        table &set_cell_value_fmt(uint32_t row, uint32_t column, const char *fmt, Args &&...args);

        table &set_row_count(uint32_t count);
        table &set_column_count(uint32_t count);
        table &set_column_width(uint32_t column, int32_t width);
        table &add_cell_control(uint32_t row, uint32_t column, cell_control ctrl);
        table &clear_cell_control(uint32_t row, uint32_t column, cell_control ctrl);
        table &set_cell_user_data(uint16_t row, uint16_t column, void *user_data);
        table &set_selected_cell(uint16_t row, uint16_t column);
        const char *get_cell_value(uint32_t row, uint32_t column);
        uint32_t get_row_count();
        uint32_t get_column_count();
        int32_t get_column_width(uint32_t column);
        bool has_cell_control(uint32_t row, uint32_t column, cell_control ctrl);
        table &get_selected_cell(uint32_t *row, uint32_t *column);
        void *get_cell_user_data(uint16_t row, uint16_t column);
    };

    template <typename... Args>
    table &table::set_cell_value_fmt(uint32_t row, uint32_t column, const char *fmt, Args &&...args)
    {
        lv_table_set_cell_value_fmt(lv_object(), row, column, fmt, std::forward<Args>(args)...);

        return *this;
    }

    inline table::cell_control operator|(const table::cell_control lhs, const table::cell_control rhs)
    {
        return static_cast<table::cell_control>(
            static_cast<uint8_t>(lhs) |
            static_cast<uint8_t>(rhs));
    }
}
