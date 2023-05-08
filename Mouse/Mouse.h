#pragma once

#include <GL/freeglut.h>

class Mouse{
public:
	int hit_pos_x, hit_pos_y;
	int move_pos_x, move_pos_y;
	int button_kind = -1;
	
	void mouse_hit(int button, int state, int x, int y);
	void wheel_scroll();
};

