#pragma once
#include <SDL2/SDL.h>
struct Theme {
    static SDL_Color BUTTON_BACKGROUND;
    static SDL_Color BUTTON_HOVER_BACKGROUND;
    static SDL_Color BUTTON_FOREGROUND;
    static SDL_Color BUTTON_BORDER;
    static int       BUTTON_PADDING_X;
    static int       BUTTON_PADDING_Y;

    static SDL_Color ENTRY_FOREGROUND;
    static SDL_Color ENTRY_PLACEHOLDER_FOREGROUND;
    static SDL_Color ENTRY_BACKGROUND;
    static SDL_Color ENTRY_BORDER;
    static SDL_Color ENTRY_CURSOR;

    static SDL_Color LABEL_FOREGROUND;
    static SDL_Color LABEL_BACKGROUND;
    static SDL_Color WINDOW_BACKGROUND;
    
    static SDL_Color SLIDER_CIRCLE;
    static SDL_Color SLIDER_BACKGROUND;
    static SDL_Color SLIDER_CLICK_BACKGROUND;
    static SDL_Color SLIDER_FOREGROUND;

    static SDL_Color CHECKBOX_BACKGROUND;
    static SDL_Color CHECKBOX_PRESS_BACKGROUND;
    static SDL_Color CHECKBOX_FOREGROUND;
    static SDL_Color CHECKBOX_CHECK;

    static SDL_Color DROPDOWN_BACKGROUND;
    static SDL_Color DROPDOWN_BORDER;
    static SDL_Color DROPDOWN_FOREGROUND;
    static SDL_Color DROPDOWN_HOVER_BACKGROUND;
    
    static SDL_Color TEXT_BACKGROUND;
    static SDL_Color TEXT_FOREGROUND;
};