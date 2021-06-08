#include <SDL2/SDL_ttf.h>
#include "Window.hpp"
#include "Checkbox.hpp"

Checkbox::Checkbox(Parent* parent, std::string _text, bool* _variable)
:Widget(parent, 0, 0, 0, 0) {
	text = Text(window, _text);
	variable = _variable;
	if (variable != nullptr) {
		checked = *variable;
	}
	update_dimensions();
}

void Checkbox::update_dimensions() {
	TTF_SizeText(window->get_font(), text.get().c_str(), &w, &h);
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
	window->draw_rect(x + padding_x + 1, y + h / 2 - 6 + 1, 10, 10, { box_bg_r, box_bg_r, box_bg_r }, true); // background
	window->draw_rect(x + padding_x, y + h / 2 - 6, 12, 12, { 255,255,255 }); // border
	text.render(x + spacing + padding_x, y + h / 2 - window->get_font_height() / 2, { f_r, f_g, f_b }); // text
	if (checked) {
		// draw the tick
		// ugly!
		window->draw_rect(x + padding_x + 2, y + h / 2 - 6 + 2, 8, 8, { 255,255,255 }, true); // border
	}
}

void Checkbox::on_press() {
	Widget::on_press();
	box_bg_r = 22;
	box_bg_g = 22;
	box_bg_b = 22;
}

void Checkbox::on_release() {
	Widget::on_release();
	box_bg_r = 28;
	box_bg_g = 28;
	box_bg_b = 28;
	checked = !checked;
	if (variable != nullptr)
		*variable = !*variable;
}