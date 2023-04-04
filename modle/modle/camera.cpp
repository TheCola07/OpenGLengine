#include "camera.h"
#include <iostream>
#include <math.h>

static float r = 200;
static float c = 3.1415926 / 180.0f;

Camera::Camera() {
	point = Vector3(0.0f, 0.0f, -1.0f);
	toward = Vector3(0.0f, 0.0f, 201.0f);
	upward = Vector3(0.0f, 1.0f, 0.0f);
	rightward = toward.Mutiply(upward);
}

void Camera::mouseMove(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		oldPosX = x; oldPosY = y;
	}
}

void Camera::changeViewPoint(int x, int y) {
	int temp = x - oldPosX;
	degree += (temp * 0.5);
	temp = y - oldPosY;
	thera += (temp * 0.5);
	if (thera < 1)
		thera = 1;
	else if (thera > 179)
		thera = 179;

	oldPosX = x;
	oldPosY = y;

	toward.x = r * cos(c * degree) * sin(c * thera);
	toward.z = r * sin(c * degree) * sin(c * thera);
	toward.y = r * cos(c * thera);
	rightward = toward.Mutiply(upward);
}

void Camera::keyBoardMove(unsigned char key, int x, int y) {
	Vector3 temp;
	switch (key) {
	case 'w':
		temp = toward;
		temp *= speed;
		point += temp;
		break;
	case 's':
		temp = toward;
		temp *= -speed;
		point += temp;
		break;
	case 'd':
		temp = rightward;
		temp *= speed;
		point += temp;
		break;
	case 'a':
		temp = rightward;
		temp *= -speed;
		point += temp;
		break;
	case ' ':
		point.y += 200 * speed;
		break;
	case 'x':
		point.y -= 200 * speed;
		break;
	}
}

void Camera::draw() {
	Vector3 eye = point + toward;
	gluLookAt(point.x, point.y, point.z, eye.x, eye.y, eye.z, upward.x, upward.y, upward.z);
}