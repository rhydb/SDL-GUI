#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>

class Text {
public:
    Text() {}
    Text(std::string text);
    void set(std::string new_text);
    std::string get();
    void render(int x, int y, SDL_Color foreground = {255, 255, 255}, bool draw_background = false, SDL_Color background = {0, 0, 0});
    int get_line_count();
    int get_width();
private:
    int width = 0;
    std::vector<std::string> lines;
};