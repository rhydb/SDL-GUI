#pragma once
#include "Slider.hpp"

class SliderInt : public Slider {
public:
	SliderInt(Parent* parent, int min, int max, int* variable = nullptr);
	void update_and_render(float dt);
	int get() { 
		return position_x / gap;
	}
	void set(int value);
	int* variable;
	bool show_lines = false;
private:
	int min = 0;
	int max = 10;
	int gap;
};