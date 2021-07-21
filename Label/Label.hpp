#pragma once

#include "Text.hpp"
#include "Widget.hpp"
class Label : public Widget, public Text {
public:
    Label(Parent* parent, std::wstring text);
    void update_and_render(float dt);
    SDL_Color foreground = {255,255,255};
    SDL_Color background = { 22, 22, 22 };
    bool show_background = false;
    void set(std::wstring new_text);
    void grid(int row, int column);
    void set_y(int newy);
private:
    int text_x;
    int text_y;
};