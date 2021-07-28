#pragma once

#include "Widget.hpp"

class Progressbar : public Widget
{
public:
    Progressbar(Parent* parent, int max);
    Progressbar(Parent* parent, int min, int max);
    void update_and_render(float dt);
private:
};
