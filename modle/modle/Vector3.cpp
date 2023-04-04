#include "Vector3.h"

Vector3::Vector3() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3::Vector3(float num1, float num2, float num3) {
	x = num1;
	y = num2;
	z = num3;
}

void Vector3::operator=(Vector3 vec) {
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
}

void Vector3::operator*=(float num) {
	this->x *= num;
	this->y *= num;
	this->z *= num;
}

void Vector3::operator+=(Vector3 vec) {
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
}

Vector3 Vector3::Mutiply(Vector3 vec) {
	float xm = this->y * vec.z - this->z * vec.y;
	float ym = -(this->x * vec.z - this->z * vec.x);
	float zm = this->x * vec.y - this->y * vec.x;
	return Vector3(xm, ym, zm);
}

Vector3 Vector3::operator+(Vector3 vec) {
	float xm = this->x + vec.x;
	float ym = this->y + vec.y;
	float zm = this->z + vec.z;
	return Vector3(xm, ym, zm);
}

Vector3 Vector3::operator*(float num) {
	float xm = this->x * num;
	float ym = this->y * num;
	float zm = this->z * num;
	return Vector3(xm, ym, zm);
}