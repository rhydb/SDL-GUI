#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "Theme.hpp"
class Window;
class Text {
public:
    Text() {}
    Text(Window* window, std::wstring text);
    virtual void set(std::wstring new_text);
    std::wstring get();
    void render(int x, int y, SDL_Color foreground = Theme::TEXT_FOREGROUND, bool draw_background = false, SDL_Color background = Theme::TEXT_BACKGROUND);
    int get_line_count();
    int get_width();
    Window* window = nullptr;
protected:
    std::wstring text;
private:
    int width = 0;
    std::vector<std::wstring> lines;
};