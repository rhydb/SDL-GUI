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
    root.resizable(true);
    root.background(150, 150, 150);
    root.dimensions(500, 200);

    Label* name_label = new Label(&root, "Text:");
    name_label->set_tooltip("hello!");
    name_label->grid(0, 0);

    Entry* name_entry = new Entry(&root);
    name_entry->set_placeholder("Placeholder...");
    name_entry->set_tooltip("name entry");
    name_entry->grid(0, 1);

    root.run();
    root.clean();
    return 0;
}