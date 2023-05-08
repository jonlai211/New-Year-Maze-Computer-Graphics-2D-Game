#include "Phone.h"

void Phone::draw() {
	base.iconArrow(-130, 240, 4);
	base.iconReset(0, -300);
	base.FillRoundRec(0, -300, 150, 30, 15, 278.f, 0.31, 1.f, 1);
	base.FillRoundRec(0, -360, 150, 10, 5, 0.f, 0.f, 0.97, 0.5);
	base.RoundRec(0, -100, 300, 300, 10, GL_LINE_LOOP, 16.f, 0.89, 0.74);		// display area of the maze
	base.FillRoundRec(0, -50, 330, 640, 20, 0.f, 0.f, 0.f, 1);					// phone inner screen
	base.FillRoundRec(0, -50, 350, 660, 30, 255.f, 0.29, 0.44, 1);				// phone outer frame
}