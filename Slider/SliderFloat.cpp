#include "SliderFloat.hpp"
#include "EventHandler.hpp"
SliderFloat::SliderFloat(Parent* parent, float _min, float _max, float* _variable)
	:Slider(parent) {
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

void SliderFloat::update_and_render(float dt) {
	if (dragging) {
		position_x = EventHandler::get_mouse_x();
		if (position_x > x + w) {
			position_x = x + w;
		}
		else if (position_x < x) {
			position_x = x;
		}
		if (variable != nullptr)
			*variable = min + get_percentage() * (max - min);
	}
	else {
		if (variable != nullptr) {
			*variable = min + get_percentage() * (max - min);
			position_x = *variable;
		}
	}
	Slider::update_and_render(dt);
}