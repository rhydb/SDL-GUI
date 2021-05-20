#include "Rect.hpp"
Rect::Rect(const Rect &other) : Rect(other.x, other.y, other.w, other.h) { }
Rect::Rect(int _x, int _y, int width, int height) :
    SDL_Rect() {
    x = _x;
    y = _y;
    w = width;
    h = height;
}
bool Rect::contains(const Rect &other) const noexcept {
    if (x > other.x) return false;
    if (y > other.y) return false;
    if (x + w  < other.x + other.w) return false;
    if (y + h < other.y + other.h) return false;
    return true; // within bounds
}
bool Rect::intersects(const Rect &other) const noexcept {
    if (x > other.x + other.w)  return false;
    if (x + w < other.x)        return false;
    if (y > other.y + other.h) return false;
    if (y + h < other.y)       return false;
    return true; // intersection
}

float Rect::get_left()   const noexcept { return x - (w  * 0.5f); }
float Rect::get_top()    const noexcept { return y + (h * 0.5f); }
float Rect::get_right()  const noexcept { return x + (w  * 0.5f); }
float Rect::get_bottom() const noexcept { return y - (h * 0.5f); }