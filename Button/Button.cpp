#include "Window.hpp"
#include "Button.hpp"
#include "Utils.hpp"
#include <iostream>
Button::Button(Parent *parent, std::string _text, std::function<void()> callback)
// hard code font height and width :)
: Widget(parent), callback(callback) {
    text = Text(window, _text);
    update_dimensions();
}

void Button::update_dimensions() {
    //w = text.get_width() * 7 + padding_x;
    //h = text.get_line_count() * 15 + padding_y;
    // TODO: this stops set_w from working
    TTF_SizeText(window->get_font(), text.get().c_str(), &w, &h);
    w += padding_x;
    h *= text.get_line_count();
    h += padding_y;
}

void Button::set_x(int newx) {
    x = newx;
    text_x = (x + w / 2) - ((text.get_width() * window->get_font_width()) / 2);
}

void Button::set_y(int newy) {
    y = newy;
    text_y = (y + h / 2) - ((text.get_line_count() * window->get_font_height()) / 2);
}

void Button::grid(unsigned int row, unsigned int column) {
    Widget::grid(row, column);
    update_dimensions();
}

void Button::update_and_render(float dt) {
    window->draw_rect(x, y, w, h, border); // border
    window->draw_rect(x+1, y+1, w-2, h-2, background, true); // background
    text.render(text_x, text_y, foreground);
    Widget::update_and_render(dt);
}

void Button::on_hover() {
    Widget::on_hover();
    window->set_cursor(Window::Cursor::HAND);
    background = Theme::BUTTON_HOVER_BACKGROUND;
}
void Button::off_hover() {
    Widget::off_hover();
    window->set_cursor(Window::Cursor::NORMAL);
    background = Theme::BUTTON_BACKGROUND;
}

void Button::on_press() {

}

void Button::on_release() {
    callback();
}

void Button::set(std::string _text) {
    text.set(_text);
    update_dimensions();
}

void Button::on_key_press(SDL_Scancode key) {
    if (key == SDL_SCANCODE_RETURN || key == SDL_SCANCODE_SPACE)
        on_hover();
}

void Button::on_key_release(SDL_Scancode key) {
    if (key == SDL_SCANCODE_RETURN || key == SDL_SCANCODE_SPACE) {
        on_hover();
        on_release();
    }
}