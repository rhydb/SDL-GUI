#pragma once
#include "Widget.hpp"
class Entry : public Widget {
public:
    Entry(Parent* parent);
    void set_placeholder(std::wstring text);
    inline void set(std::wstring text) {contents = text;}
    inline std::wstring get() {return contents;}
    void update_and_render(float dt);
    void on_hover();
    void off_hover();
    void on_select();
    void on_deselect();
    void on_press(); 
    void on_key_press(SDL_Scancode key);
    void on_key_release(SDL_Scancode key);
    void on_text_input(char* text);

private:
    int text_width = 1;
    int text_height = 1;

    bool shift = false;
    int characters = 0;
    std::wstring contents;
    std::wstring placeholder;
    int cursor_x = 2;
    int cursor_position = 0;
    bool typing = false;


    int scroll_right = 0;
    void move_cursor_right();
    void move_cursor_left();


};