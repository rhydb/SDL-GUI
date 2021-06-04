#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <thread>
#include "EventHandler.hpp"
#include "Window.hpp"

#define GET_KEY(x) SDL_GetKeyName(SDL_GetKeyFromScancode(x))
int Window::window_count = 0;

Window::Window() {
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
    window_id = SDL_GetWindowID(window);
    //windows[window_id] = this;
    SDL_SetWindowResizable(window, SDL_FALSE);
    if (window == nullptr) {
        SDL_LogError(0, "Failed to create window: %s", SDL_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // | SDL_RENDERER_PRESENTVSYNC)
    if (renderer == nullptr) {
        SDL_LogError(0, "Failed to create renderer, window_id=%d: %s", window_id, SDL_GetError());
        return;
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
    
    window_count++;
}

void Window::run() {
    
    if (!custom_dimension) {
        width = 0;
        height = 0;
        for (int h : row_heights)
            height += h;
        for (int w : column_widths)
            width += w;
        dimensions(width, height);
    }
    EventHandler::register_window(this);

    if (window_count > 1) {
        // new thread
        std::thread loop_thread(&Window::loop, this);
        loop_thread.detach();

        //loop();

    }
    else {
        // start the event handler
        float last_time = 0.0f;
        float delta_time = 0.0f;
        while (running) {
            EventHandler::get().Poll();
            update_and_render(delta_time);
            delta_time = SDL_GetTicks() - last_time;
            delta_time /= 1000;
            last_time = SDL_GetTicks();
        }
        clean();
    }
}

void Window::loop() {
    float last_time = 0.0f;
    float delta_time = 0.0f;
    while (running) {
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
    //windows.erase(window_id);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    if (window_count == 0)
        SDL_Quit();
}

void Window::update_and_render(float dt) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255); // background
    SDL_RenderClear(renderer);
    Parent::update_and_render(dt); // update children
    for (int i = 0; i < top_level.size(); i++) {
        top_level[i]();
    }
    top_level.clear();
#ifdef DEBUG
    int total = 0;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int w : column_widths) {
        SDL_RenderDrawLine(renderer, w + total, 0, w + total, height);
        total += w;
    }
    total = 0;
    for (int h : row_heights) {
        SDL_RenderDrawLine(renderer, 0, h + total, width, h + total);
        total += h;
    }
#endif

    SDL_RenderPresent(renderer);
}

void Window::title(const char *title) {
    SDL_SetWindowTitle(window, title);
}
void Window::quit() {
    window_count--;
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
    SDL_DestroyTexture(texture);
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
