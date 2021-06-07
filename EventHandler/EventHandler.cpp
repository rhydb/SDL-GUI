#include "EventHandler.hpp"

void EventHandler::Poll() {
    SDL_StartTextInput();
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_WINDOWEVENT: {
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_CLOSE: {
                        std::cout << "[CLOSE] event.window.windowID=" << event.window.windowID << "\twindow_id=" << windows[event.window.windowID]->window_id << std::endl;
                        windows[event.window.windowID]->quit();
                    } break;
                    case SDL_WINDOWEVENT_FOCUS_GAINED: {
                        windows[event.window.windowID]->focused = true;
                        focused_window_id = event.window.windowID;
                    } break;
                    case SDL_WINDOWEVENT_FOCUS_LOST: {
                        windows[event.window.windowID]->focused = false;
                        if (selected_widget != nullptr) {
                            selected_widget->on_deselect();
                            selected_widget = nullptr;
                        }
                    } break;
                    case SDL_WINDOWEVENT_SIZE_CHANGED: {
                        windows[event.window.windowID]->width = event.window.data1;
                        windows[event.window.windowID]->height = event.window.data2;
                    } break;
                    case SDL_WINDOWEVENT_ENTER: {
                        mouse_focused_window_id = event.window.windowID;
                    } break;
                    case SDL_WINDOWEVENT_LEAVE: {
                        if (selected_widget != nullptr) {
                            selected_widget->on_deselect();
                            selected_widget = nullptr;
                        }
                        if (current_hover != nullptr) {
                            current_hover->off_hover();
                            current_hover = nullptr;
                        }
                    } break;
                }
            } break;
            case SDL_TEXTINPUT: {
                if (selected_widget != nullptr) {
                    selected_widget->on_text_input(event.text.text);
                }
            } break;
            case SDL_QUIT: {
                std::cout << "Quit event\n";
                //quit();
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
                Widget* widget = windows[focused_window_id]->on_hover(mouse_x, mouse_y);
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
                Widget* widget = windows[focused_window_id]->on_hover(mouse_x, mouse_y);
                if (widget != nullptr)
                    widget->on_release();
            } break;
            case SDL_MOUSEMOTION: {
                if (mouse_focused_window_id == focused_window_id) {
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    Widget* prev_hover = current_hover;
                    current_hover = windows[focused_window_id]->on_hover(mouse_x, mouse_y);
                    if (current_hover != prev_hover) {
                        if (prev_hover != nullptr)
                            prev_hover->off_hover();
                        if (current_hover != nullptr)
                            current_hover->on_hover();
                    }
                }
            } break;
        }
    }
    SDL_StopTextInput();
}

void EventHandler::set_mouse_wheel(int state) {
    if (state > 0) {
        // scroll up
        mouse_wheel_up = true;
    }
    else if (state < 0) {
        //scroll down
        mouse_wheel_down = true;
    }
}