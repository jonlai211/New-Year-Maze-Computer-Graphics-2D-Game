#include "Firework.h"

Firework::Firework(float cx, float cy, float maxSpeed, float centerHue) {
	this->cx = cx;
	this->cy = cy;
	this->maxSpeed = maxSpeed;
	this->centerHue = centerHue;
	Base base;

	for (int i = 0; i < numBalls; i++) {
		float speed = maxSpeed * getRandf(1.f);
		base.setCenter(cx, cy);
		base.setRadius(0.5f + getRandf(3.f));
		base.setColor(centerHue - 10 + getRandf(20), 1, 1);
		base.setVelocity(speed * cosf(i * 3.14 / 180), speed * sinf(i * 3.14 / 180));
		base.setLuminanceFactor(0.2f + getRand(600) / 1000.f);
		balls.push_back(base);
	}
}

bool Firework::nextState() {
	timeToLive -= 16;
	if (timeToLive < 0) {
		return false;
	}
	for (int i = 0; i < numBalls; ++i) {
		balls[i].nextState();
	}
	return true;
}

void Firework::show() {
	for (int i = 0; i < numBalls; ++i) {
		balls[i].show();
	}
}