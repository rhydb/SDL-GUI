
#pragma once
#include <SDL2/SDL.h>
#include "Renderer.hpp"
#include "Parent.hpp"
#include "Widget.hpp"
class Widget;
class Window : public Parent {
public:
    Window();
    void title(const char *title);
    inline void background(int red, int green, int blue) {Renderer::background(red,green,blue);}
    void run();
    void dimensions(int _width, int _height) {
        width = _width;
        height = _height;
        SDL_SetWindowSize(window, _width, _height);
    }
    void quit();
    void clean();
    void resizable(bool resizable) {SDL_SetWindowResizable(window, resizable ? SDL_TRUE : SDL_FALSE);}
    int get_mouse_x() {return mouse_x;}
    int get_mouse_y() {return mouse_y;}
    Window* get_root() {return this;}
private:
    SDL_Window *window;
    Widget *current_hover = nullptr;
    Widget* selected_widget = nullptr;
    int width = 1280;
    int height = 720;
    bool running = true;
    void poll_events();
    void update_and_render();
    void set_mouse_wheel(int state);
    bool mouse_wheel_up = false;
    bool mouse_wheel_down = false;
    int mouse_x = 0;
    int mouse_y = 0;
};