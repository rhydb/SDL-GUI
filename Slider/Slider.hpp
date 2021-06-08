#pragma once

#include "Widget.hpp"

class Slider : public Widget {
public:
	Slider(Parent* parent, std::string text = "");
	void update_and_render(float dt);
	void on_press();
	void on_release();
	void on_deselect();
	float get_percentage();
private:
	int position_x = 25;
	bool dragging = false;
	SDL_Color circle_color = { 55, 55, 55 };
};