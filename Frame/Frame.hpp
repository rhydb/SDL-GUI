#pragma once

#include "Widget.hpp"
#include "Parent.hpp"

class Frame : public Widget, public Parent {
public:
    Frame(Parent* parent);
    void grid(Widget *widget, unsigned int row = -1, unsigned int column = -1); // parent grid, grid an item into the frame
    void grid(unsigned int row = -1, unsigned int column = -1); // widget grid, grid the actual frame into its parent
    void update_and_render(float dt);
    Window* get_root() {return parent->get_root();}
    void set_x(int newx);
    void set_y(int newy);

private:
    int row, column;
};