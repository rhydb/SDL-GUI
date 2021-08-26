#include <string.h>
#include "Window.hpp"
#include "Entry.hpp"
#include "EventHandler.hpp"
#include "Theme.hpp"
#include "text_handling.hpp"
Entry::Entry(Parent *parent)
: Widget(parent) {
    w = window->get_font_width() * 10; // minimum width of 10 characters (if there is no palceholder)
    h = window->get_font_height() * 1.5; // some padding
}

void Entry::update_and_render(float dt) {
    window->draw_rect(x, y, w, h, Theme::ENTRY_BORDER); // border
    window->draw_rect(x+1, y+1, w-2, h-2, Theme::ENTRY_BACKGROUND, true); // background
    if (!contents.empty()) {
        window->draw_text(x + 2, y+h/2 - window->get_font_height() / 2, visible_text.c_str(), Theme::ENTRY_FOREGROUND); // entered text
    } else {
        if (!placeholder.empty() && !typing) {// draw the placeholder
            window->draw_text(x + 2, y + h / 2 - window->get_font_height() / 2, placeholder.c_str(), Theme::ENTRY_PLACEHOLDER_FOREGROUND); // will go outside the box if long enough!
        }
    }
    if (typing)
        window->draw_rect(x + cursor_x, y+h/2 - window->get_font_height() / 2, 2, window->get_font_height(), Theme::ENTRY_CURSOR, true); // cursor
    Widget::update_and_render(dt);
}

void Entry::move_cursor_right() {
    if (contents[cursor_position] != '\0') {
        do {
            cursor_position++;
        } while(IS_NOT_START_BYTE(contents[cursor_position]));

        if (cursor_x < w - window->get_font_width()) {
            cursor_x += window->get_font_width();
        }
        else {
            scroll_right++;
        }
    }
}

void Entry::move_cursor_left() {
    if (cursor_position > 0) {
        do {
            cursor_position--;
        } while (IS_NOT_START_BYTE(contents[cursor_position]));

        if (cursor_x > window->get_font_width() + 2 || cursor_x > 2 && scroll_right == 0) {
            cursor_x -= window->get_font_width();
        }
        else {
            scroll_right--;
        }
    }
}

void Entry::on_text_input(char* text) {
    contents.insert(cursor_position, text);
    move_cursor_right();
    TTF_SizeText(window->get_font(), contents.c_str(), &text_width, &text_height);
    calc_visible_text();
}

void Entry::on_key_press(SDL_Scancode key) {

    switch (key) {
        case SDL_SCANCODE_RIGHT: {
            move_cursor_right();
        } break;
        case SDL_SCANCODE_LEFT: {
            move_cursor_left();
        } break;
        case SDL_SCANCODE_DELETE: {
            if (cursor_position < contents.size())
                contents.erase(contents.begin() + cursor_position);
        } break;
        case SDL_SCANCODE_BACKSPACE: {
            if (cursor_position > 0) {
                while (IS_NOT_START_BYTE(contents[cursor_position-1])) {
                    contents.erase(contents.begin() + cursor_position-1);
                    cursor_position--;
                }
                contents.erase(contents.begin() + cursor_position-1);
                move_cursor_left();

            }
        } break;
        default: {
        } break;
    }
    TTF_SizeText(window->get_font(), contents.c_str(), &text_width, &text_height);
    calc_visible_text();
}

void Entry::calc_visible_text() {
    visible_text.clear();
    int new_scroll_right = scroll_right;
    while (new_scroll_right > 0 && IS_NOT_START_BYTE(contents[new_scroll_right])) {
        new_scroll_right--;
    }
    for (int i = new_scroll_right; contents[i] != '\0' && ( strgetmblen(visible_text.c_str()) < (w / window->get_font_width()) || IS_NOT_START_BYTE(contents[i])); i++) {
        visible_text.push_back(contents[i]);
    }
}

void Entry::set(std::string text) {
    scroll_right = 0;
    contents = text;
    calc_visible_text();
}

void Entry::set_placeholder(std::string text) {
    placeholder = text;
    w = window->get_font_width() * text.length();
}

void Entry::on_select() {
    Widget::on_select();
    typing = true;
}

void Entry::on_press() {
    Widget::on_press();
    int mouse_x_rel = EventHandler::get_mouse_x() - x; // relative mouse x
    int character = mouse_x_rel / window->get_font_width(); // character without respect to scroll
    if (character > contents.size())
        character = contents.size();
    cursor_x = character * window->get_font_width(); // round it back up so that it locks to characters
    if (cursor_x > visible_text.size() * window->get_font_width()) {
        cursor_x = visible_text.size() * window->get_font_width();
    }
    cursor_position = scroll_right + character; // the true position
    if (cursor_position > contents.size()) {
        cursor_position = contents.size();
    }
}

void Entry::on_deselect() {
    typing = false;
}

void Entry::on_hover() {
    Widget::on_hover();
    window->set_cursor(Window::Cursor::TYPE);
}

void Entry::off_hover() {
    Widget::off_hover();
    window->set_cursor(Window::Cursor::NORMAL);
}
