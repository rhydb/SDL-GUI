#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>
class Window;
class Text {
public:
    Text() {}
    Text(Window* window, std::string text);
    virtual void set(std::string new_text);
    std::string get();
    void render(int x, int y, SDL_Color foreground = {255, 255, 255}, bool draw_background = false, SDL_Color background = {0, 0, 0});
    int get_line_count();
    int get_width();
    Window* window = nullptr;
protected:
    std::string text;
private:
    int width = 0;
    std::vector<std::string> lines;
};