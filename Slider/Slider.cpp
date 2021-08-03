#include "EventHandler.hpp"
#include "Window.hpp"
#include "Slider.hpp"


Slider::Slider(Parent* parent)
:Widget(parent) {
	w = 100;
	h = 20;
}

void Slider::update_and_render(float dt) {
	Widget::update_and_render(dt);
	window->draw_line(x, y + h / 2, x + position_x, y + h / 2, foreground); // progress line
	window->draw_line(x + position_x, y + h / 2, x + w, y + h / 2, background);

	window->draw_line(x + position_x, y+5, x + position_x, y+h-5, {255, 255, 255});

	/*
	window->draw_circle_fill(position_x + x, y + h / 2, 5, circle_border); // circle border
	window->draw_circle_fill(position_x + x, y + h / 2, 4, circle_color);
	*/
}

float Slider::get_percentage() {
	return (float)position_x / (float)w;
}

void Slider::on_press() {
	Widget::on_press();
	dragging = true;
	circle_color = Theme::SLIDER_CLICK_BACKGROUND;
}

void Slider::on_release() {
	Widget::on_release();
	dragging = false;
	circle_color = Theme::SLIDER_BACKGROUND;
}

void Slider::on_deselect() {
	Widget::on_deselect();
	dragging = false;
	circle_color = Theme::SLIDER_BACKGROUND;
}