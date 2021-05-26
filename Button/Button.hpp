#pragma once

#include <functional>
#include "Widget.hpp"
#include "Parent.hpp"
#include "Text.hpp"

class Button : public Widget {
public:
    Button(Parent *parent, std::string text, std::function<void()> callback = [](){});
    void set(std::string text);
    void update_and_render();
    void on_hover();
    void off_hover();
    void on_press();
    void on_release();
    void on_key_press(SDL_Scancode key);
    void on_key_release(SDL_Scancode key);
    void grid(int row, int column);
    inline void set_background(Uint8 r, Uint8 g, Uint8 b) {b_r = r; b_g = g; b_b = b;}
    inline void set_foreground(Uint8 r, Uint8 g, Uint8 b) {f_r = r; f_g = g; f_b = b;}
    void set_x(int new_x);
    void set_y(int new_y);
private:

    void update_dimensions();
    // foreground
    Uint8 f_r = 255;
    Uint8 f_g = 255;
    Uint8 f_b = 255;
    // background
    Uint8 b_r = 0;
    Uint8 b_g = 0;
    Uint8 b_b = 0;

    int padding_y = 10;
    int padding_x = 30;
    int text_y;
    int text_x;

    std::function<void()> callback;
    Text text;
};