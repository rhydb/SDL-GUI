#include "Frame.hpp"
Frame::Frame(Parent *parent)
: Widget(parent)  {
    type = WidgetType::FRAME;
}

void Frame::set_x(int newx) {
    int difference = newx - x;
    for (int i = 0; i < objects.size(); i++) {
        for (int j = 0; j < objects[i].size(); j++) {
            objects[i][j]->set_x(objects[i][j]->get_x() + difference);
        }
    }
    x = newx;
    m_x = x;
}

void Frame::set_y(int newy) {
    int difference = newy - y;
    for (int i = 0; i < objects.size(); i++) {
        for (int j = 0; j < objects[i].size(); j++) {
            objects[i][j]->set_y(objects[i][j]->get_y() + difference);
        }
    }
    y = newy;
    m_y = y;
}

void Frame::grid(Widget *widget, unsigned int _row, unsigned int _column) {
    Parent::grid(widget, _row, _column);

    w = 0;
    for (int width : column_widths) {
        w += width;
    }
    h = 0;
    for (int height : row_heights) {
        h += height;
    }
    widget->set_x(widget->get_x() + x);
    widget->set_y(widget->get_y() + y);
}

void Frame::grid(unsigned int _row, unsigned int _column) {
    Widget::grid(_row, _column);
    row = _row;
    column = _column;
    m_x = x;
    m_y = y;
}

void Frame::update_and_render(float dt) {
    Parent::update_and_render(dt);
    Widget::update_and_render(dt);
}