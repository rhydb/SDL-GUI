#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "Renderer.hpp"

void Renderer::_hook(SDL_Window* window) {
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
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // | SDL_RENDERER_PRESENTVSYNC)
    if (renderer == nullptr) {
        SDL_LogError(0, "Failed to create renderer: %s", SDL_GetError());
        return;
    }
    font = TTF_OpenFont("C:/Windows/Fonts/Consola.ttf", 14);
    if (!font) {
        SDL_LogError(0, "Failed to load font: %s", TTF_GetError());
        return;
    }
    TTF_SizeText(Renderer::get_font(), "a", &font_width, &font_height);
    cursor_normal = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    cursor_hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
}

void Renderer::_render() {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255); // background
    SDL_RenderPresent(renderer);
}

void Renderer::_draw_text(int x, int y, const char* text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect src = {0, 0, surface->w, surface->h};
    float w = x;
    float h = y;
    SDL_Rect dst = {w, h, src.w, src.h};
    SDL_RenderCopy(renderer, texture, &src, &dst);
    SDL_FreeSurface(surface);
}

void Renderer::_draw_rect(int x, int y, int w, int h, SDL_Color color, bool fill) {
    SDL_Rect rect = {x, y, w, h};
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    if (fill)
        SDL_RenderFillRect(renderer, &rect);
    else
        SDL_RenderDrawRect(renderer, &rect);
}
