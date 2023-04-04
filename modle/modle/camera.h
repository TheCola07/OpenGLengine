#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <vector>
#include <gl/glut.h>
#include "Vector3.h"
using namespace std;

class Camera {
public:
	Camera();
	void mouseMove(int button, int state, int x, int y);
	void changeViewPoint(int x, int y);
	void keyBoardMove(unsigned char key, int x, int y);
	void draw();
	Vector3 getRight() { return rightward; }
	Vector3 getUp() { return rightward.Mutiply(toward); }

private:
	Vector3 point;				//相机本身的位置坐标
	Vector3 toward;			//相机的朝向
	Vector3 upward;			//相机相对上方向量
	Vector3 rightward;		//相机的右方向

	float degree = 90;		//横向
	float thera = 90;			//纵向

	int oldPosY = -1;
	int oldPosX = -1;
	
	float speed = 0.05f;
};

#endif