#include "Widget.hpp"
#include "Window.hpp"
Widget::Widget(Parent *parent, int x, int y, int w, int h)
:parent(parent), x(x), y(y), w(w), h(h) {
    window = parent->get_root();
}

void Widget::grid(int row, int column) {
    parent->grid(this, row, column);
}

void Widget::update_and_render() {
    if (show_tooltip && has_tooltip) {
        tooltip.render(window->get_mouse_x() + 15, window->get_mouse_y() + 15, {255, 255, 255}, true, {0, 0, 0});
    }
}
void Widget::on_hover() {
    show_tooltip = true;
}

void Widget::off_hover() {
    show_tooltip = false;
}

void Widget::set_tooltip(std::string text) {
    has_tooltip = true;
    tooltip.set(text);
}

void Widget::remove_tooltip() {
    has_tooltip = false;
}