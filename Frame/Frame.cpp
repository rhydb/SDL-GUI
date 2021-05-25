#include "Frame.hpp"
#include "Renderer.hpp"
Frame::Frame(Parent *parent)
: Widget(parent, 0, 0, 0, 0)  {
}

void Frame::set_x(int newx) {
    int difference = newx - x;
    for (std::vector<Widget*> row : objects) {
        for (Widget* w : row) {
            w->set_x(w->get_x() + difference);
        }
    }
    x = newx;
    m_x = x;
}

void Frame::set_y(int newy) {
    int difference = newy - y;
    for (std::vector<Widget*> row : objects) {
        for (Widget* w : row) {
            w->set_y(w->get_y() + difference);
        }
    }
    y = newy;
    m_y = y;
}

void Frame::grid(Widget *widget, int _row, int _column) {
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

void Frame::grid(int _row, int _column) {
    Widget::grid(_row, _column);
    row = _row;
    column = _column;
    m_x = x;
    m_y = y;
   
}

void Frame::update_and_render() {
    Parent::update_and_render();
    Widget::update_and_render();
    Renderer::draw_rect(x, y, w, h, { 255, 0, 0 });

}