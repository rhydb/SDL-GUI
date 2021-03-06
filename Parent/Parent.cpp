#include "Parent.hpp"
#include "EventHandler.hpp"
#include <assert.h>
#include <iostream>

Widget* Parent::on_hover_grid(int x, int y) {
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

Widget* Parent::on_hover_place(int x, int y) {
    for (int i = objects.back().size()-1; i >= 0; i--) {
        if (x <= objects.back()[i]->get_x() + objects.back()[i]->get_w() &&
            x >= objects.back()[i]->get_x() &&
            y <= objects.back()[i]->get_y() + objects.back()[i]->get_h() &&
            y >= objects.back()[i]->get_y()) {
            return objects.back()[i]->get_target_widget(x, y);
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

void Parent::place(Widget *widget, unsigned int x, unsigned int y, bool center) {
    placement = Placement::PLACE;
    get_fp = &Parent::on_hover_place;
    if(objects.empty()){
        objects.push_back({});
    }
    if (center) {
        widget->set_x(x - widget->get_w() / 2);
        widget->set_y(y - widget->get_h() / 2);
    } else {
        widget->set_x(x);
        widget->set_y(y);
    }
    objects.back().push_back(widget);
}

void Parent::grid(Widget *widget, unsigned int row, unsigned int column) {
    placement = Placement::GRID;
    get_fp = &Parent::on_hover_grid;
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
    widget->set_row(row);
    widget->set_column(column);

}