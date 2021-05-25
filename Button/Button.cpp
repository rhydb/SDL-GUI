#include "Button.hpp"
#include "Window.hpp"
#include "Utils.hpp"
#include <iostream>
Button::Button(Parent *parent, std::string _text, std::function<void()> callback)
// hard code font height and width :)
: Widget(parent, 0, 0, 0, 0), callback(callback) {
    text = Text(_text);
    update_dimensions();
}

void Button::update_dimensions() {
    //w = text.get_width() * 7 + padding_x;
    //h = text.get_line_count() * 15 + padding_y;
    TTF_SizeText(Renderer::get_font(), text.get().c_str(), &w, &h);
    w += padding_x;
    h += padding_y;
    h *= text.get_line_count();
}

void Button::set_x(int newx) {
    x = newx;
    text_x = (x + w / 2) - ((text.get_width() * 7) / 2);
}

void Button::set_y(int newy) {
    y = newy;
    text_y = (y + h / 2) - ((text.get_line_count() * 15) / 2);
}

void Button::grid(int row, int column) {
    Widget::grid(row, column);
    update_dimensions();
}

void Button::update_and_render() {
    Renderer::draw_rect(x, y, w, h, {b_r, b_g, b_b}, true);
    text.render(text_x, text_y, {f_r, f_g, f_b});
    Widget::update_and_render();
}

void Button::on_hover() {
    Widget::on_hover();
    Renderer::set_cursor(Renderer::Cursor::HAND);
    Utils::swap(&f_r, &b_r);
    Utils::swap(&f_g, &b_g);
    Utils::swap(&f_b, &b_b);
}
void Button::off_hover() {
    Widget::off_hover();
    Renderer::set_cursor(Renderer::Cursor::NORMAL);
    Utils::swap(&f_r, &b_r);
    Utils::swap(&f_g, &b_g);
    Utils::swap(&f_b, &b_b);
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