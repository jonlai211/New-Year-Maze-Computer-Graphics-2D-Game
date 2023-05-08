#include "Mouse.h"

void Mouse::mouse_hit(int button, int state, int x, int y)
{
	button_kind = button;
	switch (button_kind)
	{
	case GLUT_LEFT_BUTTON:			// also have GLUT_MIDDLE_BUTTON
		if (state == GLUT_DOWN)		// also have GLUT_UP
		{
			int hit_pos_x = x;
			int hit_pos_y = y;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			hit_pos_x = x;
			hit_pos_y = y;
		}
		break;
	default:
		break;
	}
}

void wheel_scroll(){}