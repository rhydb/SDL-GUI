#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#define DEBUG_DRAW

class Renderer {
public:
    enum Cursor {NORMAL, HAND, TYPE};
    static Renderer& get() {
        static Renderer instance;
        return instance;
    }
    static void clear() {
        SDL_RenderClear(get().renderer);
    }
    static void render() {
        get()._render();
    }
    static void draw_text(int x, int y, const char* text, SDL_Color color = {255, 255, 255, 255}) {
        get()._draw_text(x, y, text, color);
    }
    static void draw_rect(int x, int y, int w, int h, SDL_Color color, bool fill = false) {
        get()._draw_rect(x, y, w, h, color, fill);
    }
    static void hook(SDL_Window* window) {
        get()._hook(window);
    }
    static inline void background(int red, int green, int blue) {get().r = red; get().b = blue; get().g = green;}

    static inline void set_cursor(Cursor cursor) {
        switch (cursor) {
            case NORMAL: {
                SDL_SetCursor(get().cursor_normal);
            }; break;
            case HAND: {
                SDL_SetCursor(get().cursor_hand);
            } break;
            case TYPE: {
                SDL_SetCursor(get().cursor_type);
            } break;
        }

    }
private:
    Renderer() {}

    void _hook(SDL_Window* window);
    void _render();
    void _draw_text(int x, int y, const char* text, SDL_Color color = {255, 255, 255, 255});
    void _draw_rect(int x, int y, int w, int h, SDL_Color color, bool fill = false);
    TTF_Font* font;

    int r = 255;
    int g = 255;
    int b = 255;
    SDL_Renderer* renderer;
    SDL_Cursor* cursor_hand;
    SDL_Cursor* cursor_normal;
    SDL_Cursor* cursor_type;
};