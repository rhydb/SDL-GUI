/*
Background: 30, 30, 30
Darker: 22, 22, 22
Middle: 28, 28, 28
Lighter: 55, 55, 55
Selected: 0, 120, 220
*/

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <functional>
#include <map>
#include "Parent.hpp"
#include "Widget.hpp"
#undef main
class Widget;
class EventHandler;
class Window : public Parent {
public:
    friend class EventHandler;
    enum Cursor { NORMAL, HAND, TYPE };
    Window();
    void title(const char* title);
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
    Window* get_root() { return this; }
    // rendering
    void draw_text(int x, int y, const char* text, SDL_Color color = { 255, 255, 255, 255 });
    void draw_rect(int x, int y, int w, int h, SDL_Color color, bool fill = false);
    void draw_line(int x1, int y1, int x2, int y2, SDL_Color color = { 0, 0, 0 });
    void draw_circle(int x, int y, int radius, SDL_Color color = {100, 100, 100});
    void draw_circle_fill(int x, int y, int radius, SDL_Color color = { 100, 100, 100 });
    void draw_rounded_rect(int x, int y, int w, int h, int r, SDL_Color color = {100, 100, 100}, bool fill = false);
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
    std::vector<std::function<int()>> click_event_callbacks; // return 1 if the click event should not be forwarded to a widget
    SDL_Color background = Theme::WINDOW_BACKGROUND;

    static int windows_created;
private:
    static int window_count;
    int sdl_window_id;
    int internal_window_id;
    SDL_Window* window;
    /*
    static std::map<int, Window*> windows;
    Widget* current_hover = nullptr;
    Widget* selected_widget = nullptr;*/
    int width = 600;
    int height = 600;
    bool custom_dimension = false;
    bool running = true;
    void update_and_render(float dt);

    bool focused = false;

    // rendering
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font;
    int font_width;
    int font_height;
    SDL_Cursor* cursor_hand;
    SDL_Cursor* cursor_normal;
    SDL_Cursor* cursor_type;

    // some functions for drawing rounded rectangle
    void DrawFillCircleTopLeft(int x, int y, int radius);
    void DrawFillCircleBottomLeft(int x, int y, int radius);
    void DrawFillCircleTopRight(int x, int y, int radius);
    void DrawFillCircleBottomRight(int x, int y, int radius);
    void DrawTopLeftCircle(int32_t centreX, int32_t centreY, int32_t radius);
    void DrawTopRightCircle(int32_t centreX, int32_t centreY, int32_t radius);
    void DrawBottomLeftCircle(int32_t centreX, int32_t centreY, int32_t radius);
    void DrawBottomRightCircle(int32_t centreX, int32_t centreY, int32_t radius);
    // end rendering
};

