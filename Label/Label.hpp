#pragma once

#include "Text.hpp"
#include "Widget.hpp"
#include "Theme.hpp"
class Label : public Widget, public Text {
public:
    Label(Parent* parent, std::wstring text);
    void update_and_render(float dt);
    SDL_Color foreground = Theme::TEXT_FOREGROUND;
    SDL_Color background = Theme::TEXT_BACKGROUND;
    bool show_background = false;
    void set(std::wstring new_text);
    void grid(unsigned int row = -1, unsigned int column = -1);
    void set_y(int newy);
private:
    int text_x;
    int text_y;
};