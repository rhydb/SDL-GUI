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
	w += padding_x * 2 + spacing;
	h *= text.get_line_count();
	h += padding_y * 2;
}

void Checkbox::grid(int row, int column) {
	Widget::grid(row, column);
	update_dimensions();
}

void Checkbox::update_and_render(float dt) {
	Widget::update_and_render(dt);
	window->draw_rect(x + padding_x, y + padding_y, 12, 12, { 0, 0, 0 }); // border
	window->draw_rect(x + padding_x + 1, y + padding_y + 1, 10, 10, { box_bg_r, box_bg_r, box_bg_r }, true);
	text.render(x + spacing + padding_x, y + padding_y, { f_r, f_g, f_b });
	if (checked) {
		// draw the tick
		// ugly!
		window->draw_line(x + padding_x + 1, y + padding_y + 1 + 5, x + padding_x + 1 + 5, y + padding_y + 1 + 10);
		window->draw_line(x + padding_x + 1 + 5, y + padding_y + 1 + 10, x + padding_x + 10, y + padding_y);
	}
}

void Checkbox::on_press() {
	Widget::on_press();
	box_bg_r = 150;
	box_bg_g = 150;
	box_bg_b = 150;
}

void Checkbox::on_release() {
	Widget::on_release();
	box_bg_r = 255;
	box_bg_g = 255;
	box_bg_b = 255;
	checked = !checked;
	if (variable != nullptr) {
		std::cout << "before: " << *variable << "\n";
		*variable = !*variable;
		std::cout << "after: " << *variable << "\n";
	}
}