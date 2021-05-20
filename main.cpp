#include <iostream>
#include <SDL2/SDL.h>
#undef main
#include "Renderer.hpp"
#include "Button.hpp"
#include "Frame.hpp"
#include "Label.hpp"
#include "Entry.hpp"
#include "Window.hpp"

int main() {
    Window root = Window();
    root.title("hello");
    root.background(150, 150, 150);
    root.dimensions(500, 200);

    Label* name_label = new Label(&root, "Name:");
    name_label->show_background = true;
    name_label->grid(0, 0);

    Entry* a = new Entry(&root);
    a->set_placeholder("Name!");
    a->w = 150;
    a->grid(1,0);

    Button* b = new Button(&root, "Get contents");
    b->set_tooltip("tooltip!");
    b->grid(2, 0);

    Button* c = new Button(&root, "Get contents");
    c->set_tooltip("another!");
    c->grid(2, 1);


    root.run();
    root.clean();
    return 0;
}