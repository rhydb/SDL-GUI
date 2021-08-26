#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "Theme.hpp"
class Window;
class Text {
public:
    friend class Textbox;
    Text() {}
    Text(Window* window, std::string text);
    virtual void set(std::string new_text);
    std::string get();
    void render(int x, int y, SDL_Color foreground = Theme::TEXT_FOREGROUND, bool draw_background = false, SDL_Color background = Theme::TEXT_BACKGROUND);
    int get_line_count();
    int get_width();
    bool empty();
    void clear();
    Window* window = nullptr;
protected:
    std::string text;
private:
    int width = 0;
    std::vector<std::string> lines;
};