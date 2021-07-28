#include <iostream>
#include <algorithm>
#include "SDL_GUI.hpp"
#include "Theme.hpp"
int main() {
  Window root = Window();
  Entry *e = new Entry(&root);
  e->set_placeholder(L"Placeholder text..");
  e->grid(0, 0);
  root.run(); 
}