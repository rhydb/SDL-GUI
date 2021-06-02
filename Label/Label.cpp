#include "Window.hpp"
#include "Label.hpp"

Label::Label(Parent *parent, std::string text)
: Widget(parent, 0, 0, 0, 0), Text(Widget::window, text){
    set(text);
}

void Label::update_and_render(float dt) {
    Text::render(x, text_y, foreground, show_background, background);
    Widget::update_and_render(dt);
}

void Label::grid(int row, int column) {
    Widget::grid(row, column);
    set(text);
}

void Label::set(std::string new_text) {
    Text::set(new_text);
    w = get_width() * Widget::window->get_font_width();
    h = get_line_count() * Widget::window->get_font_height();
    // center the text;
    text_y = y + h / 4;
    h += h / 4;
   
    //text_y = (y + h / 2) - (get_line_count() * Widget::window->get_font_height() / 4);
}

void Label::set_y(int newy) {
    y = newy;
    text_y = (y + h / 2) - (get_line_count() * Widget::window->get_font_height() / 4);
}