#pragma once

#include "../Base/Base.h"
#include "../random/random.h"
#include <vector>

class Firework {
public:
	int numBalls = 360;
	float cx, cy;
	float maxSpeed = 700;
	float centerHue = 30;
	float timeToLive = 6000;
	float Pi = 3.14;
	std::vector<Base> balls;
	
	Firework(float cx, float cy, float maxSpeed, float centerHue);
	bool nextState();
	void show();
};