#include "Parent.hpp"
#include "Renderer.hpp"
#include <iostream>

Widget* Parent::on_hover(int x, int y) {
    int temp_x = 0;
    int temp_y = 0;
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
        if (x <= objects[row][column]->x + objects[row][column]->w &&
            x >= objects[row][column]->x &&
            y <= objects[row][column]->y + objects[row][column]->h &&
            y >= objects[row][column]->y) {
            return objects[row][column]->get_target_widget(x, y);
        }
    }
    return nullptr;
}

void Parent::update_and_render() {
    for (std::vector<Widget*> row : objects) {
        for (Widget *i : row) {
            i->update_and_render();
        }
    }

}

void Parent::grid(Widget *widget, int row, int column) {

    if (row >= objects.size()) {
        // new row
        row = objects.size();
        objects.emplace_back();
    }
    if (row >= row_heights.size()) {
        row_heights.push_back(widget->h);
    } else {
        if (widget->h > row_heights[row]) {
            row_heights[row] = widget->h;
        }
    }
    if (column >= objects[row].size()) {
        // new column
        column = objects[row].size();
        objects[row].push_back(widget);
    }
    if (column >= column_widths.size()) {
        column_widths.push_back(widget->w);
    } else {
        if (widget->w > column_widths[column]) {
            column_widths[column] = widget->w;
        }
    }

    widget->y = 0;
    for (int i = 0; i < row; i++) {
        widget->y += row_heights[i];
    }
    widget->x = 0;
    for (int i = 0; i < column; i++) {
        widget->x += column_widths[i];
    }
    objects[row][column] = widget;

}