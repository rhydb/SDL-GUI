#include <iostream>
#include "SDL_GUI.hpp"

int main() {
    Window* root = new Window();
    (new Label(root, "Enter something:"))->grid(0, 0);
    Entry* e = new Entry(root);
    e->set_placeholder("Placeholder text...");
    e->set_w(300);
    e->grid(0, 1);

    bool print_contents = true;

    Button* b = new Button(root, "Click me", [e, x = &print_contents]() {
        std::cout << "Clicked!";
        if (*x) {
            std::cout << "\tContents: '" << e->get() << "'";
        }
        std::cout << std::endl;
        });
    b->set_tooltip("Try clicking me!");
    b->grid(1, 0);

    int test = 5;
    (new Checkbox(root, "Print contents", &print_contents))->grid(1, 1);
    SliderInt* s = new SliderInt(root, 0, 10, &test);
    s->grid(2, 0);

    (new Button(root, "get %", [test = &test]() {
        *test = 9;
    }))->grid(2, 1);

    root->run();
    delete root;

    return 0;
}
