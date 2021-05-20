#include <SDL2/SDL.h>
#include "Window.hpp"
#include <iostream>
#define GET_KEY(x) SDL_GetKeyName(SDL_GetKeyFromScancode(x))

Window::Window() {
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        SDL_LogError(0, "Failed to initialize SDL_VIDEO: %s", SDL_GetError());
        return;
    }
    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("SDL-GUI Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, windowFlags);
    SDL_SetWindowResizable(window, SDL_FALSE);
    if (window == nullptr) {
        SDL_LogError(0, "Failed to create window: %s", SDL_GetError());
        return;
    }
    Renderer::hook(window);
    SDL_GetMouseState(&mouse_x, &mouse_y);
}

void Window::run() {
    while (running) {
        poll_events();
        update_and_render();
    }
}

void Window::clean() {
    for (int i = 0; i < objects.size(); i++) {
        for (int j = 0; j < objects[i].size(); j++) {
            delete objects[i][j];
        }
    }
}


void Window::poll_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: quit(); break;
            case SDL_WINDOWEVENT: {
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    width = event.window.data1;
                    height = event.window.data2;
                }
            } break;
            case SDL_KEYDOWN: {
                if (selected_widget != nullptr) {
                    selected_widget->on_key_press(event.key.keysym.scancode);
                }
            } break;
            case SDL_KEYUP: {
                if (selected_widget != nullptr) {
                     selected_widget->on_key_release(event.key.keysym.scancode);
                }
            } break;
            case SDL_MOUSEWHEEL: {
                set_mouse_wheel(event.wheel.y);
            } break;

            case SDL_MOUSEBUTTONDOWN: {
                Widget* widget = Parent::on_hover(mouse_x, mouse_y);
                if (widget != nullptr) {
                    widget->on_press();
                }
                if (widget != selected_widget) {
                    if (selected_widget != nullptr) // can these be merged?
                        selected_widget->on_deselect();
                    if (widget != nullptr)
                        widget->on_select();
                    selected_widget = widget;

                }
            } break;
            case SDL_MOUSEBUTTONUP: {
                Widget* widget = Parent::on_hover(mouse_x, mouse_y);
                if (widget != nullptr)
                    widget->on_release();
            } break;

        }
    }
    int prev_x = mouse_x;
    int prev_y = mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    if (mouse_x != prev_x || mouse_y != prev_y) {
        // mouse moved

        // check hovers
        Widget *prev_hover = current_hover;
        current_hover = Parent::on_hover(mouse_x, mouse_y);
        if (current_hover != prev_hover) {
            if (prev_hover != nullptr)
                prev_hover->off_hover();
            if (current_hover != nullptr)
                current_hover->on_hover();
        }
    }
}

void Window::update_and_render() {
    Renderer::clear();
    Parent::update_and_render(); // update children
    Renderer::render();
}
void Window::set_mouse_wheel(int state) {
    if (state > 0) {
        // scroll up
        mouse_wheel_up = true;
    } else if (state < 0) {
        //scroll down
        mouse_wheel_down = true;
    }
}
void Window::title(const char *title) {
    SDL_SetWindowTitle(window, title);
}
void Window::quit() {
    running = false;
}