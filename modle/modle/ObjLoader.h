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
	Model(string filename);		//构造函数

	void DrawPoint();				//绘制函数(顶点法线量)
	void DrawFace();				//绘制函数(计算面法向量)
	void DrawLine();
	bool setTexture(char* texturePath);//设置纹理
	GLuint getTexID() {
		return myImage.texID;
	}
	void setPoint(int x, int y, int z) {
		point.x = x;
		point.y = y;
		point.z = z;
	}

	Vector3 point;					//坐标
private:
	vector<vector<GLfloat>> vSets;	//存放顶点(x,y,z)坐标
	vector<vector<GLfloat>> vtSets;	//纹理坐标
	vector<vector<GLfloat>> vnSets;	//顶点法向量
	vector<vector<GLint>> fSets;	//存放面的三个顶点索引
	vector<vector<GLint>> ftSets;
	vector<vector<GLint>> fnSets;

	TextureImage myImage;
};

#endif