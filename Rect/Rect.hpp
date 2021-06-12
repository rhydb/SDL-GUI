#pragma once
#include <SDL2/SDL.h>
struct Rect : public SDL_Rect {

    bool contains(const Rect &other) const noexcept;
    bool intersects(const Rect &other) const noexcept;
    float get_left() const noexcept;
    float get_top() const noexcept;
    float get_right() const noexcept;
    float get_bottom() const noexcept;
    Rect(const Rect&);
    Rect(int _x = 0, int _y = 0, int width = 0, int height = 0);
};