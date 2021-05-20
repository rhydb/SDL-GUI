#pragma once

#include <SDL2/SDL.h>
#include "Text.hpp"
#include "Parent.hpp"
#include <iostream>
class Parent;
class Window;
class Widget {
public:
    virtual Widget* get_target_widget(int x, int y) {return this;}
    virtual void update_and_render();
    virtual void on_press() {}
    virtual void on_release() {}
    virtual void on_key_press(SDL_Scancode key) {}
    virtual void on_key_release(SDL_Scancode key) {}
    virtual void on_hover();
    virtual void off_hover();
    virtual void on_select() {}
    virtual void on_deselect() {}
    virtual void grid(int row, int column);
    void set_tooltip(std::string text);
    int x, y, w, h;
protected:
    Window* window;
    Parent* parent;
    Text tooltip;
    bool show_tooltip = false;
    bool has_tooltip = false;
    Widget(Parent *parent, int x, int y, int w, int h);
};