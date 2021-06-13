#pragma once
#include "Slider.hpp"

class SliderFloat : public Slider {
public:
	SliderFloat(Parent* parent, float min, float max, float* variable = nullptr);
	void update_and_render(float dt);
	float get();
	void set(float value);
private:
	float* variable;
	float min;
	float max;
};