#pragma once
#include "Widget.hpp"
class Dropdown : public Widget {

public:
    Dropdown(Parent *parent, std::wstring placeholder, std::vector<std::wstring> options);
    SDL_Color foreground = Theme::DROPDOWN_FOREGROUND;
    SDL_Color background = Theme::DROPDOWN_BACKGROUND;
    SDL_Color border = Theme::DROPDOWN_BORDER;
    SDL_Color hover_background = Theme::DROPDOWN_HOVER_BACKGROUND;
    std::wstring get();
    void set(unsigned int index);
    void update_and_render(float dt);
    void on_press();
    void on_deselect();
private:
    int dropdown_height;
    int text_triangle_gap = 20;
    int triangle_size = 10;
    int triangle_edge_gap = 10;
    bool open = false;
    std::wstring *selected = nullptr;
    std::vector<std::wstring> options;
    std::wstring placeholder;

    int handle_global_press();
};