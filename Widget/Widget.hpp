#pragma once

#include <SDL2/SDL.h>
#include "Text.hpp"
#include "Parent.hpp"
#include <iostream>
#include <map>
#include <functional>

enum WidgetType {WIDGET, WINDOW, BUTTON, FRAME};

enum class WidgetEvent {
    ON_PRESS,
    ON_RELEASE,
    ON_KEY_PRESS,
    ON_KEY_RELEASE,
    ON_HOVER,
    OFF_HOVER,
    ON_SELECT,
    ON_DESELECT,
    ON_TEXT_INPUT,
    ON_WHEEL_UP,
    ON_WHEEL_DOWN
};

class Parent;
class Window;
class Widget {
public:
    friend class Parent;
    Widget(Parent* parent);

    void bind(WidgetEvent event, std::function<void()> callback);

    virtual Widget* get_target_widget(int x, int y) {return this;}
    virtual void update_and_render(float dt);
    virtual void on_press() {call_callbacks(WidgetEvent::ON_PRESS);}
    virtual void on_release() {call_callbacks(WidgetEvent::ON_RELEASE);}
    virtual void on_key_press(SDL_Scancode key) {call_callbacks(WidgetEvent::ON_KEY_PRESS);}
    virtual void on_key_release(SDL_Scancode key) {call_callbacks(WidgetEvent::ON_KEY_RELEASE);}
    virtual void on_hover();
    virtual void off_hover();
    virtual void on_select() {call_callbacks(WidgetEvent::ON_SELECT);}
    virtual void on_deselect() {call_callbacks(WidgetEvent::ON_DESELECT);}
    virtual void on_text_input(char* text) {call_callbacks(WidgetEvent::ON_TEXT_INPUT);} // this doesnt pass the argument!
    virtual void on_wheel_up() {call_callbacks(WidgetEvent::ON_WHEEL_UP);}
    virtual void on_wheel_down() {call_callbacks(WidgetEvent::ON_WHEEL_DOWN);}
    virtual void grid(unsigned int row = -1, unsigned int column = -1);
    void regrid() {grid(row, column);}
    void set_tooltip(std::wstring text);
    inline void set_tooltip_delay(float seconds) { tooltip_delay = seconds; }
    void remove_tooltip();

    virtual void set_x(int new_x) { x = new_x; }
    virtual void set_y(int new_y) { y = new_y; }
    virtual int get_x() { return x; }
    virtual int get_y() { return y; }
    virtual void set_w(int new_w) { 
        w = new_w;
    }
    virtual int get_w() { return w; }
    virtual void set_h(int new_h) { h = new_h; }
    virtual int get_h() { return h; }
    WidgetType get_type() {return type;}
protected:
    WidgetType type = WidgetType::WIDGET;
    Window* window;
    Parent* parent;
    Text tooltip;
    bool show_tooltip = false;
    bool has_tooltip = false;
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
    unsigned int row = -1;
    unsigned int column = -1;
    float collected_time = 0;
    float tooltip_delay = 0.5;

    std::map<WidgetEvent, std::vector<std::function<void()>>> event_callbacks;
private:
    void call_callbacks(WidgetEvent event);
};