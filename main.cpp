#include <iostream>
#include <algorithm>
#include "SDL_GUI.hpp"
#include "Theme.hpp"
int main() {
  Window root = Window();
  Dropdown *d = new Dropdown(&root, L"placeholder" , {L"1", L"2", L"3"});
  d->grid(0, 0);
  (new Button(&root, L"set to 1", [d](){d->set(1);}))->grid(0, 1);
  root.run();
}