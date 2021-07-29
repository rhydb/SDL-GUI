#include <SDL2/SDL_ttf.h>
#include "Window.hpp"
#include "Checkbox.hpp"

Checkbox::Checkbox(Parent* parent, std::wstring _text, bool* _variable)
:Widget(parent) {
	text = Text(window, _text);
	variable = _variable;
	if (variable != nullptr) {
		checked = *variable;
	}
	update_dimensions();
}

void Checkbox::update_dimensions() {
	char buffer[text.get().size() * 4];
	wcstombs(buffer, text.get().c_str(), text.get().size() * 4);
	TTF_SizeText(window->get_font(), buffer, &w, &h);
	w += padding_x + spacing;
	h *= text.get_line_count();
	h += padding_y;
}

void Checkbox::grid(int row, int column) {
	Widget::grid(row, column);
	update_dimensions();
}

void Checkbox::update_and_render(float dt) {
	Widget::update_and_render(dt);
	window->draw_rect(x + padding_x + 1, y + h / 2 - 6 + 1, 10, 10, box_bg, true); // background
	window->draw_rect(x + padding_x, y + h / 2 - 6, 12, 12, { 255,255,255 }); // border
	text.render(x + spacing + padding_x, y + h / 2 - window->get_font_height() / 2, foreground); // text
	if (checked) {
		// draw the tick
		// ugly!
		window->draw_rect(x + padding_x + 2, y + h / 2 - 6 + 2, 8, 8, Theme::CHECKBOX_CHECK, true); // border
	}
}

void Checkbox::on_press() {
	Widget::on_press();
	box_bg = Theme::CHECKBOX_PRESS_BACKGROUND;
}

void Checkbox::on_release() {
	Widget::on_release();
	box_bg = Theme::CHECKBOX_BACKGROUND;
	checked = !checked;
	if (variable != nullptr)
		*variable = !*variable;
}