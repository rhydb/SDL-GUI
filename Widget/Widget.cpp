#include "Widget.hpp"
#include "Window.hpp"
#include "EventHandler.hpp"

Widget::Widget(Parent *parent)
:parent(parent) {
    window = parent->get_root();
    tooltip.window = window;
}

void Widget::bind(WidgetEvent event, std::function<void()> callback) {
    event_callbacks[event].push_back(callback);
}

void Widget::grid(unsigned int row, unsigned int column) {
    parent->grid(this, row, column);
}

void Widget::place(unsigned int x, unsigned int y, bool center) {
    parent->place(this, x, y, center);
}

void Widget::update_and_render(float dt) {
    if (show_tooltip && has_tooltip) {
        if (collected_time >= tooltip_delay) {
            window->top_level.push_back([tooltip=&tooltip, window=window]() {
                tooltip->render(EventHandler::get_mouse_x() + 15, EventHandler::get_mouse_y() + 15, Theme::TOOLTIP_FOREGROUND, true, Theme::TOOLTIP_BACKGROUND);
                });
        }
        else {
            collected_time += dt;
        }
    }
#ifdef DRAW_DEBUG
    window->draw_rect(x, y, w, h, { 255, 0, 0 });
#endif
}

void Widget::on_hover() {
    show_tooltip = true;
    collected_time = 0;
    call_callbacks(WidgetEvent::ON_HOVER);
}

void Widget::off_hover() {
    show_tooltip = false;
    collected_time = 0;
    call_callbacks(WidgetEvent::OFF_HOVER);
}

void Widget::set_tooltip(std::wstring text) {
    has_tooltip = true;
    tooltip.set(text);
}

void Widget::remove_tooltip() {
    has_tooltip = false;
}

void Widget::call_callbacks(WidgetEvent event) {
    for (auto &callback : event_callbacks[event]) {
        callback();
    }
}