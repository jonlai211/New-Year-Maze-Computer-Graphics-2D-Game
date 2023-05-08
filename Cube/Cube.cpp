#include "Cube.h"

void Cube::setposition(int id, int state, char direction) {
	if ((state == 0) and (direction == 'n')) {
		switch (id) {
		case 1:
			p[0] = -100;
			p[1] = 0;
			break;
		case 2:
			p[0] = 0;
			p[1] = 0;
			break;
		case 3:
			p[0] = 100;
			p[1] = 0;
			break;
		case 4:
			p[0] = -100;
			p[1] = -100;
			break;
		case 5:
			p[0] = 0;
			p[1] = -100;
			break;
		case 6:
			p[0] = 100;
			p[1] = -100;
			break;
		case 7:
			p[0] = -100;
			p[1] = -200;
			break;
		case 8:
			p[0] = 0;
			p[1] = -200;
			break;
		}
	}
	else if (state == 1 and ((direction == 'l') || (direction == 'r') || (direction == 'u') || (direction == 'd'))) {
		switch (direction){
		case 'u':
			p[1] = p[1] + 100;
		case 'd':
			p[1] = p[1] - 100;
		case 'l':
			p[0] = p[0] - 100;
		case 'r':
			p[0] = p[0] + 100;
		}
	}
}

void Cube::draw(int i) {
	int x = 0, y = 0;
	float alpha = 1;
	switch (p[0]) 
	{
	case -1:
		x = -100;
		break;
	case 0:
		x = 0;
		break;
	case 1:
		x = 100;
		break;
	default:
		break;
	}
	
	switch (p[1])
	{
	case -1:
		y = 0;
		break;
	case 0:
		y = -100;
		break;
	case 1:
		y = -200;
		break;
	default:
		break;
	}
	
	switch (i)
	{
	case 0:
		base.letter_H(x + 25, y, 147.f, 0.80, 0.78, 5, alpha);
		break;
	case 1:
		base.letter_A(x - 25, y, 147.f, 0.80, 0.78, 5, alpha);
		base.letter_P(x + 25, y, 147.f, 0.80, 0.78, 5, alpha);
		break;
	case 2:
		base.letter_P(x - 25, y, 147.f, 0.80, 0.78, 5, alpha);
		base.letter_Y(x + 25, y, 147.f, 0.80, 0.78, 5, alpha);
		break;
	case 3:
		base.letter_N(x + 25, y, 52.f, 1.f, 0.97, 5, alpha);
		break;
	case 4:
		base.letter_E(x - 25, y, 52.f, 1.f, 0.97, 5, alpha);
		base.letter_W(x + 25, y, 52.f, 1.f, 0.97, 5, alpha);
		break;
	case 5:
		base.letter_Y(x + 25, y, 205.f, 0.99, 1.f, 5, alpha);
		break;
	case 6:
		base.letter_E(x - 25, y, 205.f, 0.99, 1.f, 5, alpha);
		base.letter_A(x + 25, y, 205.f, 0.99, 1.f, 5, alpha);
		break;
	case 7:
		base.letter_R(x - 25, y, 205.f, 0.99, 1.f, 5, alpha);
		break;
	}
	
	if (state == 1) {
		base.FillRoundRec(x, y, 100, 100, 10, 347.f, 0.27, 0.98, 1);
	}
	else if (state == -1) {
		base.FillRoundRec(x, y, 100, 100, 10, 0.f, 0.f, 0.97, 1);
	}
}