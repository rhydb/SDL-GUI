#pragma once
#include "Widget.hpp"
#include "Text.hpp"
#include "Theme.hpp"

class Checkbox : public Widget {
public:
	Checkbox(Parent* parent, std::string text, bool* variable = nullptr);
	void update_and_render(float dt);
	void grid(unsigned int row = -1, unsigned int column = -1);
	void on_press();
	void on_release();
	bool get() { return checked; };
	void set(bool status) {
		checked = status;
		if (variable != nullptr)
			*variable = status;
	}
private:
	void update_dimensions();
	Text text;
	int spacing = 20;
	int padding_x = 5;
	int padding_y = 5;
	bool checked = false;
	bool* variable = nullptr;

	// foreground
	SDL_Color foreground = Theme::CHECKBOX_FOREGROUND;

	SDL_Color box_bg = Theme::CHECKBOX_BACKGROUND;
};