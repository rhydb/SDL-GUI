#include <assert.h>
#include "Text.hpp"
#include "Window.hpp"
#include "text_handling.hpp"
Text::Text(Window* window, std::string text) : window(window) {
    set(text);
}

void Text::set(std::string new_text) {
    text = new_text;
    lines.clear();
    lines.push_back({});
    unsigned int longest = 1;
    for (char c : new_text) {
        if (c == '\n') {
            // new line
            unsigned long long char_count = strgetmblen(lines.back().c_str());
            if (char_count > longest) {
                longest = char_count;
            }
            lines.push_back({});
        } else {
             lines.back().push_back(c);
        }
    }
    unsigned long long char_count = strgetmblen(lines.back().c_str());
    if (char_count > longest) {
        longest = char_count;
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
    
    if (window == nullptr) {
        SDL_Log("Window for text object is a nullptr");
    }

    if (draw_background)
        window->draw_rect(x, y, width * window->get_font_width() , lines.size() * window->get_font_height(), background, true);
    for (int i = 0; i < lines.size(); i++) {
        if (!lines[i].empty()) {// cant render nothing
            window->draw_text(x, y + (i * window->get_font_height()), lines[i].c_str(), foreground);
        }
    }
}

bool Text::empty() {
    for (int i = 0; i < lines.size(); i++) {
        if (!lines[i].empty()) {// cant render nothing
            return false;
        }
    }
    return true;
}

void Text::clear() {
    for (int i = 0; i < lines.size(); i++) {
        lines[i].clear();
    }
}