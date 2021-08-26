#pragma once
#include "Widget.hpp"
class Textbox : public Widget {
public:
    Textbox(Parent* parent, 
        unsigned int line_count = 10, 
        unsigned int character_count = 20
    );
    void set(std::string text);
    inline std::string get() {return contents.get();}
    void update_and_render(float dt);
    void on_hover();
    void off_hover();
    void on_select();
    void on_deselect();
    void on_press(); 
    void on_key_press(SDL_Scancode key);
    void on_text_input(char* text);
    void on_wheel_up();
    void on_wheel_down();
    SDL_Color cursor_color = Theme::ENTRY_CURSOR;
    SDL_Color background = Theme::ENTRY_BACKGROUND;
    SDL_Color foreground = Theme::ENTRY_FOREGROUND;
    SDL_Color border = Theme::ENTRY_BORDER;

private:
    // how tall/wide the text being displayed is
    int text_width = 1;
    int text_height = 1;

    unsigned int line_count;
    unsigned int character_count;

    Text contents;
    Text visible_text;
    std::string placeholder;
    int padding = 2;
    int cursor_x = padding;
    int cursor_y = padding;
    int cursor_position = 0;
    int cursor_line = 0;
    bool typing = false;

    int scroll_right = 0;
    int scroll_down = 0;
    void move_cursor_right();
    void move_cursor_left();
    void move_cursor_up();
    void move_cursor_down();
    void new_line();
    void calculate_scroll();
    void calc_visible_text();
};