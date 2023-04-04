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
	Vector3 point;				//��������λ������
	Vector3 toward;			//����ĳ���
	Vector3 upward;			//�������Ϸ�����
	Vector3 rightward;		//������ҷ���

	float degree = 90;		//����
	float thera = 90;			//����

	int oldPosY = -1;
	int oldPosX = -1;
	
	float speed = 0.05f;
};

#endif