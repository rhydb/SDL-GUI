#pragma once
#include "Widget.hpp"
class Entry : public Widget {
public:
    Entry(Parent* parent);
    void set_placeholder(std::string text);
    inline void set(std::string text) {contents = text;}
    inline std::string get() {return contents;}
    void update_and_render();
    void on_hover();
    void off_hover();
    void on_select();
    void on_deselect();

    void on_key_press(SDL_Scancode key);
    void on_key_release(SDL_Scancode key);

private:
    bool shift = false;
    std::string contents = "";
    std::string placeholder = "";
    int cursor_x = 2;
    int cursor_position = 0;
    bool typing = false;


    int scroll_right = 0;
    void move_cursor_right();
    void move_cursor_left();


};