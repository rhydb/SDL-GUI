#include <iostream>
#include <SDL2/SDL.h>
#undef main
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

    Button* button = new Button(&root, "hello!");
    button->grid(0, 0);

    Window test = Window();
    test.title("test");
    Button* a = new Button(&test, "ermmm");
    a->grid(0, 0);
    test.run();

    root.run();
    return 0;
}