#include "Frame.hpp"
#include "Renderer.hpp"
Frame::Frame(Parent *parent)
: Widget(parent, 0, 0, 0, 0)  {
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
    widget->x += x;
    widget->y += y;
}

void Frame::grid(int _row, int _column) {
    Widget::grid(_row, _column);
    row = _row;
    column = _column;
    m_x = x;
    m_y = y;
    for (std::vector<Widget*> row : objects) {
        for (Widget* w : row) {
            
            w->x += x;
            w->y += y;
        }
    }
}

void Frame::update_and_render() {
    Parent::update_and_render();
    Widget::update_and_render();

}