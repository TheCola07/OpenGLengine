#ifndef TGATEXTURE_H
#define TGATEXTURE_H

#include <GL/glut.h>
#include <iostream>

using namespace std;

//����ṹ�嶨��
typedef struct
{
	GLubyte* imageData;//ͼ������
	GLuint bpp;//�������
	GLuint width;//ͼ����
	GLuint height;//ͼ��߶�
	GLuint texID;//��Ӧ������ID
}TextureImage;

//����TGAͼ����������
bool LoadTGA(TextureImage* texture, char* fileName);

#endif