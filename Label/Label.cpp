#include "Label.hpp"

Label::Label(Parent *parent, std::string text)
: Widget(parent, 0, 0, 0, 0), Text(text){
    w = get_width() * 7;
    h = get_line_count() * 15;
}

void Label::update_and_render() {
    Text::render(x, y, foreground, show_background, background);
}