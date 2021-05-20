#include "Text.hpp"
#include "Renderer.hpp"
#include <assert.h>
Text::Text(std::string text) {
    set(text);
}

void Text::set(std::string new_text) {
    lines.clear();
    lines.push_back({});
    int longest = 1;
    for (char c : new_text) {
        if (c == '\n') {
            // new line
            if (lines.back().size() > longest) {
                longest = lines.back().size();
            }
            lines.push_back({});
        } else {
             lines.back().push_back(c);
        }
    }
     if (lines.back().size() > longest) {
         longest = lines.back().size();
     }
    width = longest;
}

std::string Text::get() {
    std::string out;
    for (std::string line : lines) {
        out.append(line);
    }
    return out;
}

int Text::get_line_count() {
    return lines.size();
}

int Text::get_width() {
    return width;
}

void Text::render(int x, int y, SDL_Color foreground, bool draw_background, SDL_Color background) {
    if (draw_background)
        Renderer::draw_rect(x, y, width * 7 , lines.size() * 15, background, true);
    int i = 0;
    for (std::string line : lines) {
        if (line.length() > 0) // cant render nothing
            Renderer::draw_text(x, y + (i * 15), line.c_str(), foreground);
        i++;
    }
}