#pragma once

#include "../Base/Base.h"
#include "../Cube/Cube.h"
#include <GL/freeglut.h>
#include <iostream>


class Phone {
public:
    int Back[10][10] = {0};
    Base base;
    Cube cube;

    void draw();
};

