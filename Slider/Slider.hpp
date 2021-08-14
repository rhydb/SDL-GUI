#pragma once

#include "Theme.hpp"
#include "Widget.hpp"

class Slider : public Widget {
public:
	Slider(Parent* parent);
	void grid(unsigned int row = -1, unsigned int column = -1);
	virtual void update_and_render(float dt);
	void on_press();
	void on_release();
	void on_deselect();
	float get_percentage();
	SDL_Color circle_color = Theme::SLIDER_CIRCLE;
	SDL_Color foreground = Theme::SLIDER_FOREGROUND;
	SDL_Color background = Theme::SLIDER_BACKGROUND;
	SDL_Color circle_border = { 255,255,255};
protected:
	int position_x = 0;
	bool dragging = false;
};