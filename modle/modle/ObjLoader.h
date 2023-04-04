#ifndef OBJLOADER_H_INCLUDED
#define OBJLOADER_H_INCLUDED

#include <gl/glut.h>
#include <vector>
#include "Vector3.h"
#include <string>
#include "tgaTexture.h"

using namespace std;

class Model {
public:
	Model(string filename);		//���캯��

	void DrawPoint();				//���ƺ���(���㷨����)
	void DrawFace();				//���ƺ���(�����淨����)
	void DrawLine();
	bool setTexture(char* texturePath);//��������
	GLuint getTexID() {
		return myImage.texID;
	}
	void setPoint(int x, int y, int z) {
		point.x = x;
		point.y = y;
		point.z = z;
	}

	Vector3 point;					//����
private:
	vector<vector<GLfloat>> vSets;	//��Ŷ���(x,y,z)����
	vector<vector<GLfloat>> vtSets;	//��������
	vector<vector<GLfloat>> vnSets;	//���㷨����
	vector<vector<GLint>> fSets;	//������������������
	vector<vector<GLint>> ftSets;
	vector<vector<GLint>> fnSets;

	TextureImage myImage;
};

#endif