#include "lvgl/table.h"

#include <lvgl.h>

namespace lvgl
{
    table::table(object &parent) : object(lv_table_create(parent.lv_object()))
    {
    }

    table::~table()
    {
    }

    table &table::set_cell_value(uint32_t row, uint32_t column, const char *text)
    {
        lv_table_set_cell_value(lv_object(), row, column, text);

        return *this;
    }

    table &table::set_row_count(uint32_t count)
    {
        lv_table_set_row_count(lv_object(), count);

        return *this;
    }

    table &table::set_column_count(uint32_t count)
    {
        lv_table_set_column_count(lv_object(), count);

        return *this;
    }

    table &table::set_column_width(uint32_t column, int32_t width)
    {
        lv_table_set_column_width(lv_object(), column, width);

        return *this;
    }

    table &table::add_cell_control(uint32_t row, uint32_t column, cell_control ctrl)
    {
        lv_table_add_cell_ctrl(lv_object(), row, column, static_cast<lv_table_cell_ctrl_t>(ctrl));

        return *this;
    }

    table &table::clear_cell_control(uint32_t row, uint32_t column, cell_control ctrl)
    {
        lv_table_clear_cell_ctrl(lv_object(), row, column, static_cast<lv_table_cell_ctrl_t>(ctrl));

        return *this;
    }

    table &table::set_cell_user_data(uint16_t row, uint16_t column, void *user_data)
    {
        lv_table_set_cell_user_data(lv_object(), row, column, user_data);

        return *this;
    }

    table &table::set_selected_cell(uint16_t row, uint16_t column)
    {
        lv_table_set_selected_cell(lv_object(), row, column);

        return *this;
    }

    const char *table::get_cell_value(uint32_t row, uint32_t column)
    {
        return lv_table_get_cell_value(lv_object(), row, column);
    }

    uint32_t table::get_row_count()
    {
        return lv_table_get_row_count(lv_object());
    }

    uint32_t table::get_column_count()
    {
        return lv_table_get_column_count(lv_object());
    }

    int32_t table::get_column_width(uint32_t column)
    {
        return lv_table_get_column_width(lv_object(), column);
    }

    bool table::has_cell_control(uint32_t row, uint32_t column, cell_control ctrl)
    {
        return lv_table_has_cell_ctrl(lv_object(), row, column, static_cast<lv_table_cell_ctrl_t>(ctrl));
    }

    table &table::get_selected_cell(uint32_t *row, uint32_t *column)
    {
        lv_table_get_selected_cell(lv_object(), row, column);

        return *this;
    }

    void *table::get_cell_user_data(uint16_t row, uint16_t column)
    {
        return lv_table_get_cell_user_data(lv_object(), row, column);
    }
}