#include "Base.h"

void Base::setCenter(float cx, float cy) {
	this->cx = cx;
	this->cy = cy;
}

void Base::setColor(float h, float s, float v) {
	while (h > 360.f) {
		h -= 360.f;
	}
	while (h < 0.f) {
		h += 360.f;
	}

	this->hsv.h = h;
	this->hsv.s = s;
	this->hsv.v = v;
}

void Base::RoundRec(int centerX, int centerY, int width, int height, float cirR, int MODE, float h, float s, float v) {
	float PI = 3.14;
	float PI_HALF = PI / 2;
	float divide = 100.0;			//high value point high precision
	float tx, ty;

	setColor(h, s, v);
	RGB_t rgb = hsv2rgb(hsv);
	glBegin(MODE);
	int opX[4] = { 1,-1,-1,1 };
	int opY[4] = { 1,1,-1,-1 };		//counting times in operation by four Quadrants
	float x = 0;
	float part = 1 / divide;
	int wSize = width / 2 - cirR;
	int hSize = height / 2 - cirR;
	for (x = 0; x < 4; x += part) {
		float rad = PI_HALF * x;	//caculate arc
		tx = cirR * cos(rad) + opX[(int)x] * wSize + centerX;
		ty = cirR * sin(rad) + opY[(int)x] * hSize + centerY;
		glVertex2f(tx, ty);
	}
	glEnd();
}

void Base::FillRoundRec(int centerX, int centerY, int width, int height, float cirR, float h, float s, float v, float alpha) {
	int lineWidth = 4;
	setColor(h, s, v);
	// Convert HSV colorspace to RGB values
	RGB_t rgb = hsv2rgb(hsv);

	glColor4f(rgb.r, rgb.g, rgb.b, alpha);
	RoundRec(centerX, centerY, width, height, cirR, GL_LINE_LOOP, h, s, v);

	glColor4f(rgb.r, rgb.g, rgb.b, alpha);
	RoundRec(centerX, centerY, width - lineWidth / 2, height - lineWidth / 2, cirR, GL_POLYGON, h, s, v);
}

void Base::show() {
	// Convert HSV colorspace to RGB values
	RGB_t rgb = hsv2rgb(this->hsv);

	glBegin(GL_POLYGON);
	glColor4f(rgb.r, rgb.g, rgb.b, alpha);
	// Draw the circle
	for (int i = 0; i <= samplingNumber; ++i) {
		glVertex2f(cx + radius * cosf(2 * Pi * i / samplingNumber),
			cy + radius * sinf(2 * Pi * i / samplingNumber));
	}

	glEnd();
}

void Base::nextState() {
	if (deleted)
		return;

	vx += -2.5f + getRandf(5.f);
	vy += -2.5f + getRandf(5.f);

	cx += vx * 16 / 1000;
	cy += vy * 16 / 1000;

	// Gravity acceleration is 500 pixels / s^2.
	vy -= 500 * 16 / 1000;

	float v_square = vx * vx + vy * vy;
	float resistance = 3.f * v_square * 16 / 1000;
	vx -= resistance * vx / v_square;
	vy -= resistance * vy / v_square;

	// luminance(t) = 0.6 ^ t, where t in seconds
	// Luminance exponential decay function
	alpha *= luminanceFactor;

	if (alpha < 0.01)
		deleted = true;

	return;
}

void Base::setRadius(float r) {
	this->radius = r;
}

void Base::setVelocity(float vx, float vy) {
	this->vx = vx;
	this->vy = vy;
}

void Base::setLuminanceFactor(float factor) {
	luminanceFactor = powf(factor, 16 / 1000.f);
}

void Base::iconReset(int centerX, int centerY) {
	letter_R(centerX - 50, centerY, 334, 1.f, 0.98, 2, 1);
	letter_E(centerX - 25, centerY, 334, 1.f, 0.98, 2, 1);
	letter_S(centerX, centerY, 334, 1.f, 0.98, 2, 1);
	letter_E(centerX + 25, centerY, 334, 1.f, 0.98, 2, 1);
	letter_T(centerX + 50, centerY, 334, 1.f, 0.98, 2, 1);
}

void Base::iconArrow(int centerX, int centerY, int t) {
	int unit = alphat_unit_pixel * t;
	FillRoundRec(centerX, centerY, 10 * unit, unit, 1, 0.f, 0.f, 0.97, 1);
	FillRoundRec(centerX + 0.5 * unit, centerY + unit, 8 * unit, unit, 1, 0.f, 0.f, 0.97, 1);
	FillRoundRec(centerX + 0.5 * unit, centerY - unit, 8 * unit, unit, 1, 0.f, 0.f, 0.97, 1);
	FillRoundRec(centerX - 1.5 * unit, centerY + 2 * unit, 3 * unit, unit, 1, 0.f, 0.f, 0.97, 1);
	FillRoundRec(centerX - 1.5 * unit, centerY - 2 * unit, 3 * unit, unit, 1, 0.f, 0.f, 0.97, 1);
	FillRoundRec(centerX - unit, centerY + 3 * unit, 2 * unit, unit, 1, 0.f, 0.f, 0.97, 1);
	FillRoundRec(centerX - unit, centerY - 3 * unit, 2 * unit, unit, 1, 0.f, 0.f, 0.97, 1);
	FillRoundRec(centerX - 0.5 * unit, centerY + 4 * unit, 2 * unit, unit, 1, 0.f, 0.f, 0.97, 1);
	FillRoundRec(centerX - 0.5 * unit, centerY - 4 * unit, 2 * unit, unit, 1, 0.f, 0.f, 0.97, 1);
}

void Base::letter_H(int centerX, int centerY, float h, float s, float v, int t, float alpha) {
	int unit = alphat_unit_pixel * t;
	FillRoundRec(centerX, centerY, 8 * unit, 2 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX - 3 * unit, centerY - 0.5 * unit, 2 * unit, 9 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX + 3 * unit, centerY - 0.5 * unit, 2 * unit, 9 * unit, 1, h, s, v, alpha);
}

void Base::letter_A(int centerX, int centerY, float h, float s, float v, int t, float alpha) {
	int unit = alphat_unit_pixel * t;
	FillRoundRec(centerX, centerY - unit, 8 * unit, 2 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX - 3 * unit, centerY - 0.5 * unit, 2 * unit, 9 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX + 3 * unit, centerY - 0.5 * unit, 2 * unit, 9 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX, centerY + 3 * unit, 8 * unit, 2 * unit, 1, h, s, v, alpha);
}

void Base::letter_P(int centerX, int centerY, float h, float s, float v, int t, float alpha) {
	int unit = alphat_unit_pixel * t;
	FillRoundRec(centerX, centerY - unit, 8 * unit, 2 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX - 3 * unit, centerY - 0.5 * unit, 2 * unit, 9 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX + 3 * unit, centerY + unit, 2 * unit, 6 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX, centerY + 3 * unit, 8 * unit, 2 * unit, 1, h, s, v, alpha);
}

void Base::letter_Y(int centerX, int centerY, float h, float s, float v, int t, float alpha) {
	int unit = alphat_unit_pixel * t;
	FillRoundRec(centerX, centerY - unit, 8 * unit, 2 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX - 3 * unit, centerY + unit, 2 * unit, 6 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX + 3 * unit, centerY - 0.5 * unit, 2 * unit, 9 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX, centerY - 4 * unit, 8 * unit, 2 * unit, 1, h, s, v, alpha);
}

void Base::letter_N(int centerX, int centerY, float h, float s, float v, int t, float alpha) {
	int unit = alphat_unit_pixel * t;
	FillRoundRec(centerX - 3 * unit, centerY - 0.5 * unit, 2 * unit, 9 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX + 3 * unit, centerY - 0.5 * unit, 2 * unit, 9 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX, centerY + 2.5 * unit, 8 * unit, 3 * unit, 1, h, s, v, alpha);
}

void Base::letter_E(int centerX, int centerY, float h, float s, float v, int t, float alpha) {
	int unit = alphat_unit_pixel * t;
	FillRoundRec(centerX, centerY - 0.5 * unit, 8 * unit, unit, 1, h, s, v, alpha);
	FillRoundRec(centerX - 3 * unit, centerY - 0.5 * unit, 2 * unit, 9 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX, centerY + 3 * unit, 8 * unit, 2 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX, centerY - 4 * unit, 8 * unit, 2 * unit, 1, h, s, v, alpha);
};

void Base::letter_W(int centerX, int centerY, float h, float s, float v, int t, float alpha) {
	int unit = alphat_unit_pixel * t;
	FillRoundRec(centerX - 3 * unit, centerY - 0.5 * unit, 2 * unit, 9 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX + 3 * unit, centerY - 0.5 * unit, 2 * unit, 9 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX, centerY - 4 * unit, 8 * unit, 2 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX, centerY - 2 * unit, 2 * unit, 6 * unit, 1, h, s, v, alpha);
}

void Base::letter_R(int centerX, int centerY, float h, float s, float v, int t, float alpha) {
	int unit = alphat_unit_pixel * t;
	FillRoundRec(centerX, centerY - unit, 8 * unit, 2 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX - 3 * unit, centerY - 0.5 * unit, 2 * unit, 9 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX + 3 * unit, centerY + unit, 2 * unit, 6 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX, centerY + 3 * unit, 8 * unit, 2 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX + 2 * unit, centerY - 2 * unit, 2 * unit, 4 * unit, 1, h, s, v, alpha);
}

void Base::letter_S(int centerX, int centerY, float h, float s, float v, int t, float alpha) {
	int unit = alphat_unit_pixel * t;
	FillRoundRec(centerX, centerY, 8 * unit, 2 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX, centerY + 3 * unit, 8 * unit, 2 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX, centerY - 4 * unit, 8 * unit, 2 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX - 3 * unit, centerY + 1.5 * unit, 2 * unit, 5 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX + 4 * unit, centerY - 2 * unit, 2 * unit, 6 * unit, 1, h, s, v, alpha);
}

void Base::letter_T(int centerX, int centerY, float h, float s, float v, int t, float alpha) {
	int unit = alphat_unit_pixel * t;
	FillRoundRec(centerX, centerY + 3 * unit, 8 * unit, 2 * unit, 1, h, s, v, alpha);
	FillRoundRec(centerX, centerY - 0.5 * unit, 2 * unit, 9 * unit, 1, h, s, v, alpha);
}