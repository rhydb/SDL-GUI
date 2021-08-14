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
	variable = _variable;
}

void SliderFloat::update_and_render(float dt) {
	if (dragging) {
		position_x = EventHandler::get_mouse_x() - x;
		if (position_x > w) {
			position_x = w;
		}
		else if (position_x < 0) {
			position_x = 0;
		}
		if (variable != nullptr)
			*variable = get(); // set the variable
	}
	else {
		if (variable != nullptr) { // set position using variable;
			float percent = *variable / max;
			position_x = percent * w;
		}
	}
	Slider::update_and_render(dt);
}

float SliderFloat::get() {
	return min + get_percentage() * (max - min);
}

void SliderFloat::set(float value) {
	if (value > max)
		value = max;
	else if (value < min)
		value = min;
	if (variable != nullptr)
		*variable = value;
	float percent = value / max;
	position_x = percent * w;
}