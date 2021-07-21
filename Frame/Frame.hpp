#pragma once

#include "Widget.hpp"
#include "Parent.hpp"

class Frame : public Widget, public Parent {
public:
    Frame(Parent* parent);
    void grid(Widget *widget, int row, int column); // parent grid, grid an item into the frame
    void grid(int row, int column); // widget grid, grid the actual frame into its parent
    void update_and_render(float dt);
    Window* get_root() {return parent->get_root();}
    Widget* get_target_widget(int x, int y);
    void set_x(int newx);
    void set_y(int newy);

private:
    int row, column;
};