#pragma once

#include <functional>
#include "Widget.hpp"
#include "Parent.hpp"
#include "Text.hpp"
#include "Theme.hpp"

class Button : public Widget {
public:
    Button(Parent *parent, std::string text, std::function<void()> callback = [](){});
    void set(std::string text);
    void update_and_render(float dt);
    void on_hover();
    void off_hover();
    void on_press();
    void on_release();
    void on_key_press(SDL_Scancode key);
    void on_key_release(SDL_Scancode key);
    void grid(unsigned int row = -1, unsigned int column = -1);
    void set_x(int new_x);
    void set_y(int new_y);
    std::function<void()> callback;
    SDL_Color foreground = Theme::BUTTON_FOREGROUND;
    SDL_Color background = Theme::BUTTON_BACKGROUND;
    SDL_Color border = Theme::BUTTON_BORDER;
private:

    void update_dimensions();

    int padding_x = Theme::BUTTON_PADDING_X;
    int padding_y = Theme::BUTTON_PADDING_Y;
    int text_y;
    int text_x;

    Text text;
};
