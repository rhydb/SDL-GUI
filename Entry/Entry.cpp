#include "Entry.hpp"
#include "Renderer.hpp"
Entry::Entry(Parent *parent)
: Widget(parent, 0, 0, Renderer::get_font_width() * 10, Renderer::get_font_height() * 1.5) {
    // 10 characters long + .5 character padding each side
    // 1 character tall + .5 character padding each side
}

void Entry::update_and_render() {
    Renderer::draw_rect(x, y, w, h, {0, 0, 0});
    Renderer::draw_rect(x+1, y+1, w-2, h-2, {255, 255, 255}, true);
    if (!contents.empty()) {
        std::string visible_text;
        for (int i = scroll_right; i < contents.size() && visible_text.size() < w / Renderer::get_font_width(); i++) {
            visible_text.push_back(contents[i]);
        }
        Renderer::draw_text(x + 2, y + Renderer::get_font_height() / 3, visible_text.c_str(), {0, 0, 0});
    } else {
        if (!placeholder.empty() && !typing)
            Renderer::draw_text(x + 2, y + Renderer::get_font_height() / 3, placeholder.c_str(), {150, 150, 150});
    }
    if (typing)
        Renderer::draw_rect(x + cursor_x, y+2, 2, h-4, {0, 0, 0}, true);
    Widget::update_and_render();
}

void Entry::move_cursor_right() {
    if (cursor_position < contents.size()) {
        cursor_position++;
        if (cursor_x < w - Renderer::get_font_width()) {
            cursor_x += Renderer::get_font_width();
        }
        else {
            scroll_right++;
        }
    }


}

void Entry::move_cursor_left() {
    if (cursor_position > 0) {
        cursor_position--;
        if (cursor_x > Renderer::get_font_width() + 2 || cursor_x > 2 && scroll_right == 0) {
            cursor_x -= Renderer::get_font_width();
        }
        else {
            scroll_right--;
        }
    }
}

void Entry::on_key_press(SDL_Scancode key) {

    switch (key) {
        case SDL_SCANCODE_RIGHT: {
            move_cursor_right();
        } break;
        case SDL_SCANCODE_LEFT: {
            move_cursor_left();
        } break;
        case SDL_SCANCODE_LSHIFT:
        case SDL_SCANCODE_RSHIFT: {
            shift = true;
            return;
        } break;
        case SDL_SCANCODE_DELETE: {
            if (cursor_position < contents.size())
                contents.erase(contents.begin() + cursor_position);
        } break;
        case SDL_SCANCODE_BACKSPACE: {
            if (cursor_position > 0) {
                contents.erase(contents.begin() + cursor_position-1);
                move_cursor_left();
            }
        } break;

        default: {
            const char* character_name = SDL_GetKeyName(SDL_GetKeyFromScancode(key));
            char character;
            if (key == SDL_SCANCODE_SPACE) {
                character = ' ';
            } else {
                if (strlen(character_name) != 1)
                    return;
                character = character_name[0];
            }
            if (character >= 33 && character <= 126) { // ! to ~
                // standard ascii letter
                if (character >= 'A' && character <= 'Z') {
                    // adjust for shift
                    if (!shift) {
                        character += 32; // a - A = 32
                    }
                } else {
                    if (shift)
                        character -= 16; // 1 - ! = 16
                }
            } else if (character != ' ') {
                return;
            }

            contents.insert(contents.begin() + cursor_position, character);
            move_cursor_right();

        } break;
    }
    TTF_SizeText(Renderer::get_font(), contents.c_str(), &text_width, &text_height);
}

void Entry::on_key_release(SDL_Scancode key) {
    if (key == SDL_SCANCODE_LSHIFT || key == SDL_SCANCODE_RSHIFT) {
        shift = false;
    }
}

void Entry::set_placeholder(std::string text) {
    placeholder = text;
}

void Entry::on_select() {
    Widget::on_select();
    typing = true;
}

void Entry::on_deselect() {
    typing = false;
}

void Entry::on_hover() {
    Widget::on_hover();
    Renderer::set_cursor(Renderer::Cursor::TYPE);
}

void Entry::off_hover() {
    Widget::off_hover();
    Renderer::set_cursor(Renderer::Cursor::NORMAL);
}
