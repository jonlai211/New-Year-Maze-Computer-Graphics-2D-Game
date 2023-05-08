#define FREEGLUT_STATIC
#include "GlobalState.h"

#define WIDTH 450
#define HEIGHT 800

GlobalState::GlobalState() {
	this->phone = new Phone();
	this->cubes = std::vector<Cube>(8);
	// init all cubes
	this->cubes.at(0).id = 1;
	this->cubes.at(0).p[0] = -1;
	this->cubes.at(0).p[1] = -1;

	this->cubes.at(1).id = 2;
	this->cubes.at(1).p[0] = 1;
	this->cubes.at(1).p[1] = -1;

	this->cubes.at(2).id = 3;
	this->cubes.at(2).p[0] = 0;
	this->cubes.at(2).p[1] = 1;

	this->cubes.at(3).id = 4;
	this->cubes.at(3).p[0] = -1;
	this->cubes.at(3).p[1] = 0;

	this->cubes.at(4).id = 5;
	this->cubes.at(4).p[0] = 0;
	this->cubes.at(4).p[1] = -1;

	this->cubes.at(5).id = 6;
	this->cubes.at(5).p[0] = -1;
	this->cubes.at(5).p[1] = 1;

	this->cubes.at(6).id = 7;
	this->cubes.at(6).p[0] = 1;
	this->cubes.at(6).p[1] = 1;

	this->cubes.at(7).id = 8;
	this->cubes.at(7).p[0] = 0;
	this->cubes.at(7).p[1] = 0;

	this->distribution_matrix[1][1] = 1;
	this->distribution_matrix[2][1] = 1;
	this->distribution_matrix[3][1] = 1;
	this->distribution_matrix[1][2] = 1;
	this->distribution_matrix[2][2] = 1;
	this->distribution_matrix[3][2] = 0;
	this->distribution_matrix[1][3] = 1;
	this->distribution_matrix[2][3] = 1;
	this->distribution_matrix[3][3] = 1;
	//DmatrixVisual(5, 5);

	// save this init globalstate for resetting later
	

	this->screen_width = 3840;
	this->screen_height = 2160;
}

GlobalState::~GlobalState() {
	free(this->phone);
}

void GlobalState::render() {
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Perform the depth test to render multiple objects in the correct order of Z-axis value
	glEnable(GL_DEPTH_TEST); // Hidden surface removal

	// Draw the background in blue-black gradient color
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -50.0f);
	glBegin(GL_POLYGON);
	// Lighter blue
	glColor3f(0.f, 0.1f, 0.2f);
	glVertex3f(-WIDTH / 2.f, -HEIGHT / 2.f, 0.f);
	glVertex3f(+WIDTH / 2.f, -HEIGHT / 2.f, 0.f);

	// Darker blue
	glColor3f(0.0f, 0.02f, 0.05f);
	glVertex3f(+WIDTH / 2.f, +HEIGHT / 2.f, 0.f);
	glVertex3f(-WIDTH / 2.f, +HEIGHT / 2.f, 0.f);
	glEnd();
	glPopMatrix();

	// Draw the puzzle
	glPushMatrix();
	for (int i = 0; i < 8; i++) {
		cubes.at(i).draw(i);
	}
	glPopMatrix();

	// Push cube.p[2] into distribution matrix
	PushCube2Dmatrix();

	// Draw the phone
	glPushMatrix();
	this->phone->draw();
	glPopMatrix();

	// Draw all the existing fireworks in the list
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -3.0f);
	for (auto it = fireworks.begin(); it != fireworks.end(); ++it) {
		(*it).show();
	}
	glPopMatrix();

	glutSwapBuffers();
}

void GlobalState::keyDown(unsigned char key, int x, int y) {
	if (key == 'q' || key == 'Q')
		exit(0);

	if (key == 'r' || key == 'R') {
		// reset the game
		Reset();
		printf("Maze has been reset! \n");
	}

	// dectect movement
	selectedCubeState();																			// find out the cube which is selected
	position2distribution(cubes.at(selected_cube_id).p[0], cubes.at(selected_cube_id).p[1]);		// output dx, dy for boarder dectect
	//DmatrixVisual(5, 5);
	if (key == 'w' || key == 'W') {
		if (distribution_matrix[dx][dy - 1] == -1) {
			printf("You are already at the border! \n");
		}
		else if (distribution_matrix[dx][dy - 1] == 1) {
			printf("Illegal movement \n");
		}
		else {
			cubes.at(selected_cube_id).p[1]--;
			distribution_matrix[dx][dy - 1] = 1;
			distribution_matrix[dx][dy] = 0;
		}
	}
	else if (key == 's' || key == 'S') {
		if (distribution_matrix[dx][dy + 1] == -1) {
			printf("You are already at the border! \n");
		}
		else if (distribution_matrix[dx][dy + 1] == 1) {
			printf("Illegal movement \n");
		}
		else {
			cubes.at(selected_cube_id).p[1]++;
			distribution_matrix[dx][dy + 1] = 1;
			distribution_matrix[dx][dy] = 0;
		}
	}
	else if (key == 'a' || key == 'A') {
		if (distribution_matrix[dx - 1][dy] == -1) {
			printf("You are already at the border! \n");
		}
		else if (distribution_matrix[dx - 1][dy] == 1) {
			printf("Illegal movement \n");
			/*printf("px:%d; py:%d \n", cubes.at(selected_cube_id).p[0], cubes.at(selected_cube_id).p[1]);*/
		}
		else {
			cubes.at(selected_cube_id).p[0]--;
			distribution_matrix[dx][dy] = 0;
			distribution_matrix[dx - 1][dy] = 1;
		}
	}
	else if (key == 'd' || key == 'D') {
		if (distribution_matrix[dx + 1][dy] == -1) {
			printf("You are already at the border! \n");
		}
		else if (distribution_matrix[dx + 1][dy] == 1) {
			printf("Illegal movement \n");
		}
		else {
			cubes.at(selected_cube_id).p[0]++;
			distribution_matrix[dx][dy] = 0;
			distribution_matrix[dx + 1][dy] = 1;
		}
	}
	position2distribution(cubes.at(selected_cube_id).p[0], cubes.at(selected_cube_id).p[1]);
	//DmatrixVisual(5, 5);
	
}

void GlobalState::mouseDown(int button, int state, int x, int y) {
	// Detect for right click
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		// Coordinate translation from screen to the world.
		float cx = (float)x / WIDTH * WIDTH - WIDTH / 2;
		float cy = -(float)y / HEIGHT * HEIGHT + HEIGHT / 2;
		// show firework at the place where mouse click
		fireworks.push_back(Firework(cx, cy, 500 + getRand(800), getRand(360)));
	}

	// Detect for left click
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouseposition2position(x, y);					// output mouse position at this moment by px, py
		position2distribution(px, py);					// output dx, dy to find out empty place
		if (px == -2 and py == -2) {
			printf("You are out of the selection area! \n");
		}
		else {
			if (distribution_matrix[dx][dy] == 0) {
				printf("This place is empty! \n");
			}
			else {
				selectedCubeState();							// check if only one cube was selected
				if (only_one_select == 1) {				// find out the last selected position and reset it
					cubes.at(selected_cube_id).state = -1;		// release the selected cube
					for (int i = 0; i < 8; i++) {
						if (cubes.at(i).p[0] == px and cubes.at(i).p[1] == py) {
							cubes.at(i).state = 1;
							break;
						}
					}
				}
				else {
					for (int i = 0; i < 8; i++) {
						if (cubes.at(i).p[0] == px and cubes.at(i).p[1] == py) {
							cubes.at(i).state = 1;
							break;
						}
					}
				}
			}
		}
	}

	// Detect interaction
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (x > WIDTH / 2 - 75 and x < WIDTH / 2 + 75 and y > HEIGHT / 2 + 280 and y < HEIGHT / 2 + 320) {
			Reset();
			printf("Maze has been reset! \n");
		}
		if (x > WIDTH / 2 - 140 and x<WIDTH / 2 - 120 and y>HEIGHT / 2 - 130 and y < HEIGHT / 2 - 110) {
			
		}
	}
}

void GlobalState::reshape(int w, int h) {
	if (h == 0) // Avoid division by zero
		h = 1;
	// Set viewport to window dimensions
	glViewport(0, 0, w, h);
	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set viewing volume
	glOrtho(-WIDTH / 2.f, WIDTH / 2.f, -HEIGHT / 2.f, HEIGHT / 2.f, -500, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// fixed window size
	glutReshapeWindow(450, 800);
}

void GlobalState::position2distribution(int px, int py) {
	if (px == -1 and py == -1) {          //1
		dx = 1; dy = 1;
	}
	else if (px == 0 and py == -1) {      //2
		dx = 2; dy = 1;
	}
	else if (px == 1 and py == -1) {      //3
		dx = 3; dy = 1;
	}
	else if (px == -1 and py == 0) {      //4
		dx = 1; dy = 2;
	}
	else if (px == 0 and py == 0) {       //5
		dx = 2; dy = 2;
	}
	else if (px == 1 and py == 0) {       //6
		dx = 3; dy = 2;
	}
	else if (px == -1 and py == 1) {      //7
		dx = 1; dy = 3;
	}
	else if (px == 0 and py == 1) {       //8
		dx = 2; dy = 3;
	}
	else if (px == 1 and py == 1) {       //9
		dx = 3; dy = 3;
	}
}

void GlobalState::distribution2position(int dx, int dy) {
	{
		if (dx == 1 and dy == 1) {        //1
			px = -1; py = -1;
		}
		else if (dx == 2 and dy == 1)     //2
		{
			px = 0; py = -1;
		}
		else if (dx == 3 and dy == 1)     //3
		{
			px = 1, py = -1;
		}
		else if (dx == 1 and dy == 2)     //4
		{
			px = -1; py = 0;
		}
		else if (dx == 2 and dy == 2)     //5
		{
			px = 0; py = 0;
		}
		else if (dx == 3 and dy == 2)     //6
		{
			px = 1; py = 0;
		}
		else if (dx == 1 and dy == 3)     //7
		{
			px = -1; py = 1;
		}
		else if (dx == 2 and dy == 3)     //8
		{
			px = 0; py = 1;
		}
		else if (dx == 3 and dy == 3)     //9
		{
			px = 1; py = 1;
		}

	}
}

void GlobalState::mouseposition2position(int mpx, int mpy) {
	if ((mpx >= WIDTH / 2 - 150) and (mpx < WIDTH / 2 - 50) and (mpy >= HEIGHT / 2 - 50) and (mpy < HEIGHT / 2 + 50)) {         //1
		px = -1, py = -1;
	}
	else if ((mpx >= WIDTH / 2 - 50) and (mpx < WIDTH / 2 + 50) and (mpy >= HEIGHT / 2 - 50) and (mpy < HEIGHT / 2 + 50)) {     //2
		px = 0, py = -1;
	}
	else if ((mpx >= WIDTH / 2 + 50) and (mpx < WIDTH / 2 + 150) and (mpy >= HEIGHT / 2 - 50) and (mpy < HEIGHT / 2 + 50)) {    //3
		px = 1, py = -1;
	}
	else if ((mpx >= WIDTH / 2 - 150) and (mpx < WIDTH / 2 - 50) and (mpy >= HEIGHT / 2 + 50) and (mpy < HEIGHT / 2 + 150)) {   //4
		px = -1, py = 0;
	}
	else if ((mpx >= WIDTH / 2 - 50) and (mpx < WIDTH / 2 + 50) and (mpy >= HEIGHT / 2 + 50) and (mpy < HEIGHT / 2 + 150)) {    //5
		px = 0, py = 0;
	}
	else if ((mpx >= WIDTH / 2 + 50) and (mpx < WIDTH / 2 + 150) and (mpy >= HEIGHT / 2 + 50) and (mpy < HEIGHT / 2 + 150)) {   //6
		px = 1, py = 0;
	}
	else if ((mpx >= WIDTH / 2 - 150) and (mpx < WIDTH / 2 - 50) and (mpy >= HEIGHT / 2 + 150) and (mpy < HEIGHT / 2 + 250)) {  //7
		px = -1, py = 1;
	}
	else if ((mpx >= WIDTH / 2 - 50) and (mpx < WIDTH / 2 + 50) and (mpy >= HEIGHT / 2 + 150) and (mpy < HEIGHT / 2 + 250)) {   //8
		px = 0, py = 1;
	}
	else if ((mpx >= WIDTH / 2 + 50) and (mpx < WIDTH / 2 + 150) and (mpy >= HEIGHT / 2 + 150) and (mpy < HEIGHT / 2 + 250)) {  //9
		px = 1, py = 1;
	}
	else if ((mpx < WIDTH / 2 - 150) || (mpx > WIDTH / 2 + 150) || (mpy < HEIGHT / 2 - 50) || (mpy > HEIGHT / 2 + 250)) {
		px = -2, py = -2;
	}
}

void GlobalState::selectedCubeState() {
	for (int i = 0; i < 8; i++) {
		if (cubes.at(i).state == 1) {
			only_one_select = true;
			selected_cube_id = i;
			return;
		}
	}
}

void GlobalState::DmatrixVisual(int x, int y) {
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			printf("%d, ", distribution_matrix[x][y]);
		}
		printf("\n");
	}
}

void GlobalState::PushCube2Dmatrix() {
	for (int i = 0; i < 8; i++) {
		if (cubes.at(i).p[0] == -1 and cubes.at(i).p[1] == -1) {
			distribution_matrix[1][1] = 1;
		}
		else if (cubes.at(i).p[0] == 0 and cubes.at(i).p[1] == -1) {
			distribution_matrix[2][1] = 1;
		}
		else if (cubes.at(i).p[0] == 1 and cubes.at(i).p[1] == -1) {
			distribution_matrix[3][1] = 1;
		}
		else if (cubes.at(i).p[0] == -1 and cubes.at(i).p[1] == 0) {
			distribution_matrix[1][2] = 1;
		}
		else if (cubes.at(i).p[0] == 0 and cubes.at(i).p[1] == 0) {
			distribution_matrix[2][2] = 1;
		}
		else if (cubes.at(i).p[0] == 1 and cubes.at(i).p[1] == 0) {
			distribution_matrix[3][2] = 1;
		}
		else if (cubes.at(i).p[0] == -1 and cubes.at(i).p[1] == 1) {
			distribution_matrix[1][3] = 1;
		}
		else if (cubes.at(i).p[0] == 0 and cubes.at(i).p[1] == 1) {
			distribution_matrix[2][3] = 1;
		}
		else if (cubes.at(i).p[0] == 1 and cubes.at(i).p[1] == 1) {
			distribution_matrix[3][3] = 1;
		}
	}
	if ((cubes.at(0).p[0] == -1 and cubes.at(0).p[1] == -1) and
		(cubes.at(1).p[0] == 0 and cubes.at(1).p[1] == -1) and
		(cubes.at(2).p[0] == 1 and cubes.at(2).p[1] == -1) and
		(cubes.at(3).p[0] == -1 and cubes.at(3).p[1] == 0) and
		(cubes.at(4).p[0] == 0 and cubes.at(4).p[1] == 0) and
		(cubes.at(5).p[0] == -1 and cubes.at(5).p[1] == 1) and
		(cubes.at(6).p[0] == 0 and cubes.at(6).p[1] == 1) and
		(cubes.at(7).p[0] == 1 and cubes.at(7).p[1] == 1)) {
		next_frame = 1;
	}
}

void GlobalState::WindowPosition2Center(int x, int y) {
	cx = x - WIDTH / 2;
	cy = y - HEIGHT / 2;
}

void GlobalState::Reset() {
	cubes.at(0).p[0] = -1;
	cubes.at(0).p[1] = -1;

	cubes.at(1).p[0] = 1;
	cubes.at(1).p[1] = -1;

	cubes.at(2).p[0] = 0;
	cubes.at(2).p[1] = 1;

	cubes.at(3).p[0] = -1;
	cubes.at(3).p[1] = 0;

	cubes.at(4).p[0] = 0;
	cubes.at(4).p[1] = -1;

	cubes.at(5).p[0] = -1;
	cubes.at(5).p[1] = 1;

	cubes.at(6).p[0] = 1;
	cubes.at(6).p[1] = 1;

	cubes.at(7).p[0] = 0;
	cubes.at(7).p[1] = 0;

	distribution_matrix[1][1] = 1;
	distribution_matrix[2][1] = 1;
	distribution_matrix[3][1] = 1;
	distribution_matrix[1][2] = 1;
	distribution_matrix[2][2] = 1;
	distribution_matrix[3][2] = 0;
	distribution_matrix[1][3] = 1;
	distribution_matrix[2][3] = 1;
	distribution_matrix[3][3] = 1;
}

/* (px,py)
   (-1,-1)|(0,-1)|(1,-1)
   (-1, 0)|(0, 0)|(1, 0)
   (-1, 1)|(0, 1)|(1, 1)
*/

/* (dx,dy)
   ( 0, 0)|(1, 0)|(2, 0)|(3, 0)|(4, 0)
   ( 0, 1)|(1, 1)|(2, 1)|(3, 1)|(4, 1)
   ( 0, 2)|(1, 2)|(2, 2)|(3, 2)|(4, 2)
   ( 0, 3)|(1, 3)|(2, 3)|(3, 3)|(4, 3)
   ( 0, 4)|(1, 4)|(2, 4)|(3, 4)|(4, 4)
*/
