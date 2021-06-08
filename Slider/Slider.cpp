#include "EventHandler.hpp"
#include "Window.hpp"
#include "Slider.hpp"


Slider::Slider(Parent* parent, std::string text)
:Widget(parent, 0, 0, 100, 20) {
	
}

void Slider::update_and_render(float dt) {
	Widget::update_and_render(dt);

	if (dragging) {
		position_x = EventHandler::get_mouse_x();
		if (position_x > x + w) {
			position_x = x + w;
		}
		else if (position_x < x) {
			position_x = x;
		}
	}

	window->draw_line(x, y + h / 2, x + position_x, y + h / 2, { 0, 120, 220 }); // progress line
	window->draw_line(x + position_x, y + h / 2, x + w, y + h / 2, { 55,55,55 });
	window->draw_circle_fill(position_x + x, y + h / 2, 5, { 255,255,255});
	window->draw_circle_fill(position_x + x, y + h / 2, 4, circle_color);
}

float Slider::get_percentage() {
	return (float)position_x / (float)w;
}

void Slider::on_press() {
	Widget::on_press();
	dragging = true;
	circle_color = { 22, 22, 22 };
}

void Slider::on_release() {
	Widget::on_release();
	dragging = false;
	circle_color = { 55, 55, 55 };
}

void Slider::on_deselect() {
	Widget::on_deselect();
	dragging = false;
	circle_color = { 55, 55, 55 };
}