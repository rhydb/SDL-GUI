#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "Window.hpp"

#define GET_KEY(x) SDL_GetKeyName(SDL_GetKeyFromScancode(x))

Window::Window() {
    static int window_id = -1;
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        SDL_LogError(0, "Failed to initialize SDL_VIDEO: %s", SDL_GetError());
        return;
    }

    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
        SDL_LogError(0, "Failed to initialize SDL_IMG: %s", TTF_GetError());
        return;
    }
    if (TTF_Init()) {
        SDL_LogError(0, "Failed to initialize TTF: %s", SDL_GetError());
        return;
    }
    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("SDL-GUI Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, windowFlags);
    SDL_SetWindowResizable(window, SDL_FALSE);
    if (window == nullptr) {
        SDL_LogError(0, "Failed to create window: %s", SDL_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(window, window_id, SDL_RENDERER_ACCELERATED); // | SDL_RENDERER_PRESENTVSYNC)
    if (renderer == nullptr) {
        SDL_LogError(0, "Failed to create renderer: %s", SDL_GetError());
        return;
    }
    std::cout << "Created window with id: " << window_id << std::endl;
    if (window_id == -1) {
        window_id = 1;
    } else {
        window_id++;
    }

    font = TTF_OpenFont("consola.ttf", 14);
    if (!font) {
        SDL_LogError(0, "Failed to load font: %s", TTF_GetError());
        return;
    }
    TTF_SizeText(font, "a", &font_width, &font_height);
    cursor_normal = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    cursor_hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);

    
    SDL_GetMouseState(&mouse_x, &mouse_y);
}

void Window::run() {
    float last_time = 0.0f;
    float delta_time = 0.0f;
    if (!custom_dimension) {
        width = 0;
        height = 0;
        for (int h : row_heights)
            height += h;
        for (int w : column_widths)
            width += w;
        dimensions(width, height);
    }
    while (running) {
        poll_events();
        update_and_render(delta_time);
        delta_time = SDL_GetTicks() - last_time;
        delta_time /= 1000;
        last_time = SDL_GetTicks();
    }
    clean();
}

void Window::clean() {
    for (int i = 0; i < objects.size(); i++) {
        for (int j = 0; j < objects[i].size(); j++) {
            delete objects[i][j];
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    // ?? SDL_Quit();
}


void Window::poll_events() {
    SDL_StartTextInput();
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_TEXTINPUT: {
                if (selected_widget != nullptr) {
                    selected_widget->on_text_input(event.text.text);
                }
            } break;
            case SDL_QUIT: {
                quit(); 
            } break;
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
    SDL_StopTextInput();
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

void Window::update_and_render(float dt) {
    SDL_RenderClear(renderer);
    Parent::update_and_render(dt); // update children
    SDL_SetRenderDrawColor(renderer, r, g, b, 255); // background
    SDL_RenderPresent(renderer);
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

// rendering

void Window::draw_text(int x, int y, const char* text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect src = {0, 0, surface->w, surface->h};
    float w = x;
    float h = y;
    SDL_Rect dst = {w, h, src.w, src.h};
    SDL_RenderCopy(renderer, texture, &src, &dst);
    SDL_FreeSurface(surface);
}

void Window::draw_rect(int x, int y, int w, int h, SDL_Color color, bool fill) {
    SDL_Rect rect = {x, y, w, h};
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    if (fill)
        SDL_RenderFillRect(renderer, &rect);
    else
        SDL_RenderDrawRect(renderer, &rect);
}
