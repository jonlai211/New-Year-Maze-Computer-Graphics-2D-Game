#pragma once

#include "../Base/Base.h"
#include "../Cube/Cube.h"
#include "../Phone/Phone.h"
#include "../Firework/Firework.h"
#include <vector>
#include <list>
using namespace std;


class GlobalState {
public:
	int next_frame = 0;
	bool only_one_select = false;
	int distribution_matrix[5][5] = { {-1, -1, -1, -1, -1},
									  {-1, -1, -1, -1, -1},
									  {-1, -1, -1, -1, -1},
									  {-1, -1, -1, -1, -1},
									  {-1, -1, -1, -1, -1} };
	std::list<Firework> fireworks;
	GlobalState();

	~GlobalState();

	void render();

	void keyDown(unsigned char key, int x, int y);

	void mouseDown(int button, int state, int x, int y);

	void reshape(int w, int h);

private:
	Phone* phone;
	std::vector<Cube> cubes;
	int screen_width, screen_height;
	int px{}, py{}, dx{}, dy{}, mpx{}, mpy{}, cx{}, cy{}, window_x{}, window_y{};
	int selected_cube_id{};

	void position2distribution(int 
		
		
		, int py);
	void distribution2position(int dx, int dy);
	void mouseposition2position(int mpx, int mpy);
	void selectedCubeState();
	void DmatrixVisual(int x, int y);
	void PushCube2Dmatrix();
	void WindowPosition2Center(int x, int y);
	void Reset();
};