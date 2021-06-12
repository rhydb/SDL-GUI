#pragma once

#include "Widget.hpp"

class Slider : public Widget {
public:
	Slider(Parent* parent);
	virtual void update_and_render(float dt);
	void on_press();
	void on_release();
	void on_deselect();
	float get_percentage();
protected:
	int position_x = 0;
	bool dragging = false;
	SDL_Color circle_color = { 55, 55, 55 };
};