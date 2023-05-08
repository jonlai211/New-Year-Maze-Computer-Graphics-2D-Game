/**
 * @file main.cpp
 *
 * @brief Main function of CPT205 assignment.
 *
 * @author Kaijie Lai 2034675
 *
 * @email Kaijie.Lai20@student.xjtlu.edu.cn
 */

#include "main.h"

static int width = 450, height = 800;
static int play_time = 0;
GlobalState game_state;

void newFireworkTimerCallback(int value) {
	// Push back the new firework with random location, color and size into the firework list.
	game_state.fireworks.push_back(Firework(getRand(width) - width / 2, 60 + getRand(300), 500 + getRand(800), getRand(360)));
	// Register this timer callback with a random period.
	glutTimerFunc(getRand(3000), newFireworkTimerCallback, value + 1);
}

void newFrameTimerCallback(int value) {

	// Update the next state for all fireworks which are still present.
	// Delete the firework from the list if the current firework is lazy deleted.
	for (auto it = game_state.fireworks.begin(); it != game_state.fireworks.end();) {
		if (!(*it).nextState()) {
			// Delete current firework and assign the next firework to it.
			it = game_state.fireworks.erase(it);
		}
		else {
			++it;
		}
	}

	glutPostRedisplay(); // force OpenGL to redraw the current window
	glutTimerFunc(TIME_INC, newFrameTimerCallback, value + TIME_INC);
}

void IdleCallback() {
    glutPostRedisplay();	
}

void RenderCallback() {
    game_state.render();
	if (game_state.next_frame == 1 and play_time == 0) {
		glutTimerFunc(0, newFireworkTimerCallback, 1);
		printf("Happy New Year!\n");
		play_time = 1;
	}
}

void KeyboardCallback(unsigned char key, int x, int y) {
    game_state.keyDown(key, x, y);
}

void MouseCallback(int button, int state, int x, int y) {
    game_state.mouseDown(button, state, x, y);
}

void ReshapeCallback(int w, int h) {
    game_state.reshape(w, h);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - width) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - height) / 2);
	glutCreateWindow("Pixel Maze");

	// Enable anti-aliasing.
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_POINT_SMOOTH);
	////glEnable(GL_LINE_SMOOTH);
	//glEnable(GL_POLYGON_SMOOTH);

	// Register the callback functions.
    glutIdleFunc(IdleCallback);
    glutReshapeFunc(ReshapeCallback);
	glutMouseFunc(MouseCallback);
    glutKeyboardFunc(KeyboardCallback);
    glutDisplayFunc(RenderCallback);

	// Timer for displaying a new frame in period of 16ms (60Hz)
	glutTimerFunc(TIME_INC, newFrameTimerCallback, 0);

	// Init the random function.
	srand(time(NULL));

	glutMainLoop();
	return 0;
}