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
button->grid(0, 0);
root.run();
```

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