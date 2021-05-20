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

}

void Frame::grid(int _row, int _column) {
    Widget::grid(row, column);

    row = _row;
    column = _column;
}

void Frame::update_and_render() {
    Parent::update_and_render();
}