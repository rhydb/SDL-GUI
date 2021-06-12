#include "Parent.hpp"
#include <assert.h>
#include <iostream>

Widget* Parent::on_hover(int x, int y) {
    int temp_x = m_x;
    int temp_y = m_y;
    int row = 0;
    int column = 0;
    for (int height : row_heights) {
        if (y >= temp_y && y <= temp_y + height) {
            // found the row
            break;
        }
        temp_y += height;
        row++;
    }
    for (int width : column_widths) {
        if (x >= temp_x && x <= temp_x + width) {
            // found the row
            break;
        }
        temp_x += width;
        column++;
    }
    if (row < objects.size() && column < objects[row].size()) {
        if (x <= objects[row][column]->get_x() + objects[row][column]->get_w() &&
            x >= objects[row][column]->get_x() &&
            y <= objects[row][column]->get_y() + objects[row][column]->get_h() &&
            y >= objects[row][column]->get_y()) {
            return objects[row][column]->get_target_widget(x, y);
        }
    }
    return nullptr;
}

void Parent::update_and_render(float dt) {
    for (int i = 0; i < objects.size(); i++) {
        for (int j = 0; j < objects[i].size(); j++) {
            objects[i][j]->update_and_render(dt);
        }
    }

}

void Parent::grid(Widget *widget, int row, int column) {
    if (row >= objects.size()) {
        // new row
        row = objects.size();
        objects.push_back(std::vector<Widget*> {});
        row_heights.push_back(widget->get_h());
    }

    if (column >= objects[row].size()) {
        // new column
        column = objects[row].size();
        objects[row].push_back(widget);
        if (column >= column_widths.size()) {
            column_widths.push_back(widget->get_w());
        }
    }
    if (widget->get_h() > row_heights[row]) {
        for (int i = row + 1; i < objects.size(); i++) {
            for (int j = 0; j < objects[i].size(); j++) {
                objects[i][j]->set_y(objects[i][j]->get_y()+ widget->get_h() - row_heights[row]);
            }
        }
        row_heights[row] = widget->get_h();
    }
    if (widget->get_w() > column_widths[column]) {
        for (int i = 0; i < objects.size(); i++) {
            for (int j = column + 1; j < objects[i].size(); j++) {
                objects[i][j]->set_x(objects[i][j]->get_x() + widget->get_w() - column_widths[column]);
            }
        }
        column_widths[column] = widget->get_w();
    }
    widget->set_y(0);
    for (int i = 0; i < row; i++) {
        widget->set_y(widget->get_y() + row_heights[i]);
    }
    widget->set_x(0);
    for (int i = 0; i < column; i++) {
        widget->set_x(widget->get_x() + column_widths[i]);
    }
    objects[row][column] = widget;


}