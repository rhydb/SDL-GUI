# SDL-GUI

A super simple tkinter-like widget based GUI toolkit to create simple C++ graphical apps.

It uses SDL2 has a backend for creating windows, rendering shapes and colours and fetching input. This information is handled and filtered through two main parent classes, *Parents* and *Widgets*.

**Parents**

- Base class for storing and organising widgets in a grid, handles event hand outs

**Widget**

- Base class for everything that gets displayed, contains all event methods.

## Usage

Creating a basic app looks something like this

```c++
Window root = Window();
Entry* entry = new Entry(&root);
entry->grid(0, 0);
Button* button = new Button(&root, "Click me", [](){
	std::cout << "I was clicked" << std::endl;
});
button->grid(0, 1);
root.run();
```

So far these widgets are implemented

- Buttons
- Labels
- Entry boxes
- Checkboxes
- Frames
- Slider (int & float)

## Dependencies

To build, the following are required

- SDL2 (`sudo apt install libsdl2-dev`)
- SDL2_ttf (`sudo apt install libsdl2-ttf-dev`)

## Usage

A valid `font.ttf` file should be in the same directory as the binary. This font should be **fixed width**. This font must be able to display any characters that you wish to display as there are no fallbacks.
Additionally, all widgets should be created using the `new` keyword (`Widget *w = new Widget()`). This is to allow for cleaning up to take place once the window's `run()` has returned.

There can be some issues with unicode on Windows due to `setlocale` which uses `setlocale(LC_ALL, ".UTF8")`, on Linux this is `setlocale(LC_ALL, "")`.

To handle unicode, all strings are `std::wstring` and to communicate with SDL, which uses c-strings, `mbstowcs` and `wcstombs` are used. This means that any in-line strings being passed to widgets should be L strings (`L"text"`).

## Organisation

Organisation can only be created using dynamic grids, meaning they will grow with the items that are 'gridded' and are bigger than previously gridded items.

Frames act as sub-grids allowing for further organisation.

Widgets will be as close as possible without crossing a row or column.

Having two widgets like this:
```
+-----++-----+
| 0,0 || 0,1 |
+-----++-----+
```

And inserting into `1,0` will cause `0,1` to move

```
+-----+   +-----+
| 0,0 |   | 0,1 |
+-----+   +-----+
+---------+
|   1,0   |
+---------+
```

To prevent `0,1` from being moved it, along with `0,0`, can be placed in a frame. This frame would be gridden in `0,0` of the main parent.

## Screenshots

![](./screenshot.png)
