
#pragma once

#include "Text.hpp"
#include "Widget.hpp"
class Label : public Widget, public Text {
public:
    Label(Parent* parent, std::string text);
    void update_and_render();
    SDL_Color foreground = {0, 0, 0};
    SDL_Color background = {255, 255, 255};
    bool show_background = false;
    void set(std::string new_text);
    void grid(int row, int column);

private:
    int text_x;
    int text_y;
};