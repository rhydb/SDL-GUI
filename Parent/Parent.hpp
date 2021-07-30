#pragma once
#include <vector>
#include "Widget.hpp"
class Widget;
class Window;
enum class Placement {GRID, PLACE};
class Parent {
public:
    virtual Widget* get_target_widget(int x, int y) {return on_hover(x, y);} // make this the main call for the window.cpp event handler !!!
    virtual void grid(Widget *widget, unsigned int row, unsigned int column);
    virtual Widget* on_hover(int x, int y);
    virtual void off_hover(int x, int y) {}
    virtual Window* get_root() {return nullptr;}
    //    void remove_widget(Widget *widget); // use linear search using the x y and grid
protected:
    std::vector<int> row_heights = {};
    std::vector<int> column_widths = {};
    std::vector<std::vector<Widget*>> objects = {}; // vector of widget vectors
    virtual void update_and_render(float dt);
    int m_x = 0;
    int m_y = 0;
    Placement placement;
    bool placement_chosen;
};