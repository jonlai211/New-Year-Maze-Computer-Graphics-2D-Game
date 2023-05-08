#pragma once

#include "../Color/Color.h"
#include "../random/random.h"
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

class Base{
public:
	float Pi = 3.14;
	float cx = 0, cy = 0;			// Coordinate of center
	float vx = 0, vy = 0;			// Velocity, pixels per second.
	float alpha = 1.f;
	float radius = 4.5;
	int samplingNumber = 12;
	float luminanceFactor = 1.f;	// Luminance exponential decay factor
	bool deleted = false;			// Lazy delete flag
	int centerX, centerY;
	int alphat_unit_pixel = 1;
	HSV_t hsv;						// Color in HSV color space
	
	void setCenter(float cx, float cy);
	void setColor(float h, float s, float v);
	void RoundRec(int centerX, int centerY, int width, int height, float cirR, int MODE, float h, float s, float v);
	void FillRoundRec(int centerX, int centerY, int width, int height, float cirR, float h, float s, float v, float alpha);
	void show();
	void nextState();
	void setRadius(float r);
	void setVelocity(float vx, float);
	void setLuminanceFactor(float factor);
	void iconReset(int centerX, int centerY);
	void iconArrow(int centerX, int centerY, int t);
	void letter_H(int centerX, int centerY, float h, float s, float v ,int t, float alpha);		// this alphat is drawn in a 10x10 square and enlarged 5 times for 100x100 square
	void letter_A(int centerX, int centerY, float h, float s, float v, int t, float alpha);
	void letter_P(int centerX, int centerY, float h, float s, float v, int t, float alpha);
	void letter_Y(int centerX, int centerY, float h, float s, float v, int t, float alpha);
	void letter_N(int centerX, int centerY, float h, float s, float v, int t, float alpha);
	void letter_E(int centerX, int centerY, float h, float s, float v, int t, float alpha);
	void letter_W(int centerX, int centerY, float h, float s, float v, int t, float alpha);
	void letter_R(int centerX, int centerY, float h, float s, float v, int t, float alpha);
	void letter_S(int centerX, int centerY, float h, float s, float v, int t, float alpha);
	void letter_T(int centerX, int centerY, float h, float s, float v, int t, float alpha);
};

