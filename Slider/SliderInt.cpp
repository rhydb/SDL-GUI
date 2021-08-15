#include "EventHandler.hpp"
#include "SliderInt.hpp"

SliderInt::SliderInt(Parent* parent, int _min, int _max, int* _variable)
	:Slider(parent), variable(_variable) {
	if (_min > _max) {
		max = _min;
		min = _max;
	}
	else {
		max = _max;
		min = _min;
	}
	if (max > w) {
		w = max;
	}
	gap = w / (max - min);
}

int SliderInt::get() {
	return position_x / gap;
}

void SliderInt::update_and_render(float dt) {
	if (dragging) {
		int mouse_x = EventHandler::get_mouse_x()-x;
		if (mouse_x > w)
			mouse_x = w;
		else if (mouse_x < 0)
			mouse_x = 0;

		int difference = mouse_x - position_x;

		while (difference >= gap || difference <= -gap) {
			if (difference >= gap)
				position_x += gap;
			else if (difference <= -gap)
				position_x -= gap;
			if (position_x > w) {
				position_x = w;
			}
			else if (position_x < 0) {
				position_x = 0;
			}
			difference = mouse_x - position_x;
		}
		if (variable != nullptr)
			*variable = get();
	}
	else {
		if (variable != nullptr) {
			position_x = *variable * gap;
		}
	}
	if (show_lines) {
		for (int i = x; i <= x + w; i += gap) {
			window->draw_line(i, y + 5, i, y + h - 5, { 55, 55, 55 });
		}
	}
	Slider::update_and_render(dt);
}

void SliderInt::set(int value) {
	if (value > max)
		value = max;
	else if (value < min)
		value = min;
	position_x = value * gap;
	if (variable != nullptr) {
		*variable = value;
	}
}