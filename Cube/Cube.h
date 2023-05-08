#pragma once

#include "../Base/Base.h"
#include <GL/freeglut.h>
#include <iostream>
#include <vector>

class Cube {
public:
    int id;
    int p[2];
    int state = -1;     //state = -1 stands unselected

    Cube() = default;
    ~Cube() = default;

    void setposition(int id, int state, char direction);

    void draw(int i);

    Base base;

};