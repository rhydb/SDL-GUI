
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <functional>
#include "Parent.hpp"
#include "Widget.hpp"
#undef main
class Widget;
class Window : public Parent {
public:
    enum Cursor { NORMAL, HAND, TYPE };
    Window();
    void title(const char* title);
    inline void background(int red, int green, int blue) { r = red; b = blue; g = green; }
    void run();
    void dimensions(int _width, int _height) {
        width = _width;
        height = _height;
        SDL_SetWindowSize(window, _width, _height);
        custom_dimension = true;
    }
    void quit();
    void clean();
    void resizable(bool resizable) { SDL_SetWindowResizable(window, resizable ? SDL_TRUE : SDL_FALSE); }
    int get_mouse_x() { return mouse_x; }
    int get_mouse_y() { return mouse_y; }
    Window* get_root() { return this; }

    // rendering
    void draw_text(int x, int y, const char* text, SDL_Color color = { 255, 255, 255, 255 });
    void draw_rect(int x, int y, int w, int h, SDL_Color color, bool fill = false);
    inline void set_cursor(Cursor cursor) {
        switch (cursor) {
        case NORMAL: {
            SDL_SetCursor(cursor_normal);
        }; break;
        case HAND: {
            SDL_SetCursor(cursor_hand);
        } break;
        case TYPE: {
            SDL_SetCursor(cursor_type);
        } break;
        }
    }
    inline int get_font_height() { return font_height; }
    inline int get_font_width() { return font_width; }
    inline TTF_Font* get_font() { return font; }
    // end rendering
    std::vector<std::function<void()>> top_level;


private:
    SDL_Window* window;
    Widget* current_hover = nullptr;
    Widget* selected_widget = nullptr;
    int width = 600;
    int height = 600;
    bool custom_dimension = false;
    bool running = true;
    void poll_events();
    void update_and_render(float dt);
    void set_mouse_wheel(int state);
    bool mouse_wheel_up = false;
    bool mouse_wheel_down = false;
    int mouse_x = 0;
    int mouse_y = 0;

    // rendering
    int r = 255;
    int g = 255;
    int b = 255;
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font;
    int font_width;
    int font_height;
    SDL_Cursor* cursor_hand;
    SDL_Cursor* cursor_normal;
    SDL_Cursor* cursor_type;
    // end rendering
};
