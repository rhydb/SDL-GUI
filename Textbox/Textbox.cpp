#include "EventHandler.hpp"
#include "Window.hpp"
#include "Textbox.hpp"

Textbox::Textbox(Parent* parent, unsigned int line_count, unsigned int character_count)
:Widget(parent), line_count(line_count), character_count(character_count) {
    w = window->get_font_width() * character_count;
    h = window->get_font_height() * line_count;
    contents = Text(window, L"");
    visible_text = Text(window ,L"");
}


void Textbox::update_and_render(float dt) {
    window->draw_rect(x, y, w, h, border); // border
    window->draw_rect(x+1, y+1, w-2, h-2, background, true); // background
    if (!contents.empty()) {
        visible_text.render(x+2, y, foreground);
        // window->draw_text(x + 2, y+h/2 - window->get_font_height() / 2, buffer_n, Theme::ENTRY_FOREGROUND); // entered text
    } else {
        if (!placeholder.empty() && !typing) {// draw the placeholder
            char buffer[placeholder.size() * 4];
            wcstombs(buffer, placeholder.c_str(), placeholder.size() * 4);
            window->draw_text(x + 2, y + h / 2 - window->get_font_height() / 2, buffer, Theme::ENTRY_PLACEHOLDER_FOREGROUND); // will go outside the box if long enough!
        }
    }
    if (typing)
        window->draw_rect(x + cursor_x, y+cursor_y, 2, window->get_font_height(), Theme::ENTRY_CURSOR, true); // cursor
    Widget::update_and_render(dt);
}

void Textbox::calc_visible_text() {
    visible_text.lines.clear();
    for (int l = scroll_down; l < contents.get_line_count() && visible_text.get_line_count() < line_count; l++) {
        // go through each line visible after the scroll down, and add characters visible after scroll right
        visible_text.lines.push_back(L"");
        for (int i = scroll_right; i < contents.lines[l].length() && visible_text.lines.back().size() < character_count; i++) {
            visible_text.lines.back().push_back(contents.lines[l][i]);
        }
    }
}

void Textbox::set(std::wstring text) {
    contents.set(text);
    scroll_right = 0;
    scroll_down = 0;
    calc_visible_text();
}

void Textbox::calculate_scroll() {
    if (cursor_position > contents.lines[cursor_line].size()) {
        cursor_x = contents.lines[cursor_line].size() * window->get_font_width() + padding;
        cursor_position = contents.lines[cursor_line].size();
        if (cursor_position > character_count) {
            scroll_right = cursor_position - character_count + 1;
        } else {
            scroll_right = 0;
        }
    }
    if (cursor_position > character_count) {
        cursor_x = w - padding;
    }
}

void Textbox::move_cursor_up() {
    if (cursor_line > 0) {
        cursor_line--;
        if (cursor_line-scroll_down < 0) {
            scroll_down--;
        } else {
            cursor_y -= window->get_font_height();
        }
        calculate_scroll();
    }
}

void Textbox::move_cursor_down() {
    if (cursor_line+1 < contents.get_line_count()) {
        cursor_line++;
        if (cursor_line-scroll_down >= line_count) {
            scroll_down++;
        } else {
            cursor_y += window->get_font_height();
        }
        calculate_scroll();
    }

}

void Textbox::move_cursor_right() {
    cursor_position++;
    if (cursor_position > contents.lines[cursor_line].size()) {
        // cursor has gone past the line
        if (cursor_line < contents.get_line_count()-1) {
            //wrap to the next line
            cursor_position = 0;
            cursor_x = padding;
            cursor_line++;
            if (cursor_line-scroll_down+1 > visible_text.get_line_count()) {
                scroll_down++;
                cursor_x = padding;
            } else {
                cursor_y += window->get_font_height();
            }
            scroll_right = 0;
        } else {
            cursor_position--; // dont do anything as there isn't anymore text
        }
    } else {
        if (cursor_position-scroll_right >= character_count) {
            // cursor has gone past the visible text, scroll
            scroll_right++;
        } else {
            cursor_x += window->get_font_width();
        }
    }
}

void Textbox::move_cursor_left() {
    cursor_position--;
    cursor_x -= window->get_font_width();
    if (cursor_position - scroll_right < 0) {
        // cursor has gone before the line
        if (scroll_right > 0) {
            scroll_right--;
            cursor_x += window->get_font_width();
        } else {
            cursor_line--;
            if (cursor_line < 0) {
                // no more text before
                cursor_line = 0;
                cursor_x = padding;
                cursor_position++;
            } else {
                // just go up a line
                if (cursor_line < scroll_down) {
                    // has the cursor gone before the visible text
                    scroll_down--;
                } else {
                    cursor_y -= window->get_font_height();
                }
                cursor_x = contents.lines[cursor_line].size();
                cursor_position = contents.lines[cursor_line].size();
                if (cursor_x > character_count) {
                    // put the cursor to the end of the line above
                    scroll_right = cursor_position - character_count + 1;
                    cursor_x = character_count;
                }
                cursor_x *= window->get_font_width();
                cursor_x+=padding;
            }
        }
    }
}

void Textbox::new_line() {
    // TODO: if new_line in the middle of a line, take the right side of the cursor with it
    std::wstring right_side = contents.lines[cursor_line].substr(cursor_position, std::wstring::npos); // all text to the right of cursor
    contents.lines[cursor_line].erase(cursor_position, std::wstring::npos);
    contents.lines.insert(contents.lines.begin() + cursor_line+1, right_side);
    move_cursor_down();
    cursor_position = 0; // put cursor at the beginning of the line
    cursor_x = padding;
}

// events

void Textbox::on_select() {
    Widget::on_select();
    typing = true;
}

void Textbox::on_deselect() {
    typing = false;
}

void Textbox::on_hover() {
    Widget::on_hover();
    window->set_cursor(Window::Cursor::TYPE);
}

void Textbox::off_hover() {
    Widget::off_hover();
    window->set_cursor(Window::Cursor::NORMAL);
}

void Textbox::on_press() {
    Widget::on_press();
    int mouse_x_rel = EventHandler::get_mouse_x() - x; // relative mouse x
    int mouse_y_rel = EventHandler::get_mouse_y() - y; // relative mouse y
    int line = mouse_y_rel / window->get_font_height();
    if (line >= visible_text.get_line_count()) {
        line = visible_text.get_line_count()-1;
    }
    int character = mouse_x_rel / window->get_font_width(); // character without respect to scroll
    if (character > contents.lines[line].size())
        character = contents.lines[line].size();

    cursor_y = line * window->get_font_height();
    if (cursor_y > (visible_text.get_line_count() - 1) * window->get_font_height()) {
        cursor_y = (visible_text.get_line_count() - 1) * window->get_font_height();
    }
    cursor_x = character * window->get_font_width(); // round it back up so that it locks to characters
    if (cursor_x > visible_text.lines[line].size() * window->get_font_width()) {
        cursor_x = visible_text.lines[line].size() * window->get_font_width();
    }
    cursor_position = scroll_right + character;
    if (cursor_position > contents.lines[line + scroll_down].size()) {
        cursor_position = contents.lines[line + scroll_down].size();
    }
    cursor_line = line+scroll_down;
}

void Textbox::on_text_input(char* text) {
    wchar_t buffer_w[strlen(text) * 4];
    mbstowcs(buffer_w, text, strlen(text) * 4);
    contents.lines[cursor_line].insert(cursor_position, buffer_w);
    move_cursor_right();

    calc_visible_text();
}

void Textbox::on_key_press(SDL_Scancode key) {
    switch (key) {
        case SDL_SCANCODE_RIGHT: move_cursor_right(); break;
        case SDL_SCANCODE_LEFT: move_cursor_left(); break;
        case SDL_SCANCODE_UP: move_cursor_up(); break;
        case SDL_SCANCODE_DOWN: move_cursor_down(); break; 
        case SDL_SCANCODE_RETURN: new_line(); break;
        case SDL_SCANCODE_DELETE: {
            if (cursor_position < contents.lines[cursor_line].size())
                contents.lines[cursor_line].erase(contents.lines[cursor_line].begin() + cursor_position);
        } break;
        case SDL_SCANCODE_BACKSPACE: {
            if (cursor_position > 0) {
                contents.lines[cursor_line].erase(contents.lines[cursor_line].begin() + cursor_position-1);
                move_cursor_left();
            } else {
                if (cursor_line > 0) {
                    contents.lines.erase(contents.lines.begin() + cursor_line);
                    move_cursor_up();
                    cursor_position = -1;
                    calculate_scroll();
                }
            }
        } break;
        default: {
        } break;
    }
    // char buffer_n[contents.size() * 4];
    // wcstombs(buffer_n, contents.c_str(), contents.size() * 4);
    // TTF_SizeText(window->get_font(), buffer_n, &text_width, &text_height);
    calc_visible_text();
}

void Textbox::on_wheel_up() {
    move_cursor_up();
    calc_visible_text();
}


void Textbox::on_wheel_down() {
    move_cursor_down();
    calc_visible_text();
}