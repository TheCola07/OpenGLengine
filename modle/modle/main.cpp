#include <iostream>
#include "ObjLoader.h"
#include "camera.h"


using namespace std;

//ģ��·��
string filePath = "E:/openGL/J20/J20.obj";

Model objModel = Model(filePath);
Camera camera = Camera();

//���Ʊ���
//static float c = 3.1415926 / 180.0f;
//static float r = 200.0f;
//static int degree = 90;				//�������
//static int thera = 90;				//�������
//static vector<GLfloat> over = {0.0f, 1.0f, 0.0f};
//static vector<GLfloat> look = {0.0f, 0.0f, 0.0f};
static int oldPosY = -1;
static int oldPosX = -1;
static float alpha = 0;
static int changeMethod = 1;
static int lightContorl = 1;//��Դ����
static int handMove = -1;
static int timeIdle = 0;

void subMenu(int value) {
	if (value == 1) changeMethod = 1;
	if (value == 2) changeMethod = 0;
	if (value == 3) changeMethod = 2;
	if (value == 4) lightContorl *= -1;
	if (value == 5) handMove *= -1;
}

void myMainMenu(int value) {
	if (value == 1) changeMethod = 1;
	if (value == 2) changeMethod = 0;
	if (value == 3) changeMethod = 2;
	if (value == 4) lightContorl *= -1;
	if (value == 5) handMove *= -1;
	if (value == 6) exit(0);
}

//���ù�Դ
void setLightRes() {
	GLfloat lightPosition[] = {0.0f, 0.0f, 1.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	if (lightContorl == 1) {
		glEnable(GL_LIGHTING);	//������Դ
		glEnable(GL_LIGHT0);	//ʹ��ָ����Դ
	} else {
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);	//ʹ��ָ����Դ
	}
}

//��ʼ��
void init() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(1024 / 2 - 250, 768 / 2 - 250);
	glutCreateWindow("ObjLoader");
	glEnable(GL_DEPTH_TEST);

	if(!objModel.setTexture("E:/openGL/J20/j20.tga")) {
		std::cout << "�������ʧ��" << std::endl;
	}

	//�˵�����
	int sub_menu = glutCreateMenu(subMenu);
	glutAddMenuEntry("�����", 1);
	glutAddMenuEntry("����ر�", 2);
	glutAddMenuEntry("�߿�ģ��", 3);
	glutAddMenuEntry("��Դ����", 4);
	glutAddMenuEntry("��ק���أ���ʱ��", 5);
	glutCreateMenu(myMainMenu);
	glutAddSubMenu("������Ʒ���", sub_menu);
	glutAddMenuEntry("�˳�", 6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);          //���ô��ڱ���ɫΪ��ɫ

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	setLightRes();
	glEnable(GL_DEPTH_TEST);
}

void display() {
	glColor3f(1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);
	setLightRes();
	glPushMatrix();
	//gluLookAt(r * cos(c * degree) * sin(c * thera), r * cos(c * thera), r * sin(c * degree) * sin(c * thera), look[0], look[1], look[2], over[0], over[1], over[2]);
	camera.draw();

	glTranslatef(-100.0f, 0.0f, 0.0f);
	glutSolidCube(10);
	glTranslatef(100.0f, 0.0f, 0.0f);

	//����ģ��
	glTranslatef(objModel.point.x, objModel.point.y, objModel.point.z);
	glPushMatrix();
	glRotatef(alpha, 0.0f, 1.0f, 0.0f);
	if (changeMethod == 0) {
		objModel.DrawFace();
	} else if (changeMethod == 1){
		objModel.DrawPoint();
	} else if (changeMethod == 2) {
		objModel.DrawLine();
	}
	glPopMatrix();

	glTranslatef(0.0f, 0.0f, -5.0f);
	glPopMatrix();
	glutSwapBuffers();

	
}

//���ڴ�С����
void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLdouble)width / (GLdouble)height, 1.0f, 2000.0f);
	glMatrixMode(GL_MODELVIEW);
}

//������
void moseMove(int button, int state, int x, int y) {
	if (handMove == 1) {
		if (state == GLUT_DOWN) {
			oldPosX = x; oldPosY = y;
		}
	} else {
		camera.mouseMove(button, state, x, y);
	}
}

//���̲���
void mykeyboard(unsigned char key, int x, int y) {
	/*
	timeIdle = 0;
	switch (key) {
	case 'w':
	case 'W':
		r -= 2.0f;
		break;
	case 's':
	case 'S':
		r += 2.0f;
		break;
	}

	if (r < 0.1f)
		r = 0.1f;
	*/
	camera.keyBoardMove(key, x, y);
}

//����ƶ�����
void changeViewPoint(int x, int y) {
	if (handMove == 1) {
		int tempX = x - oldPosX;
		int tempY = y - oldPosY;
		
		objModel.point += (camera.getRight() * (tempX / 1000.0f));
		objModel.point += (camera.getUp() * ( - tempY / 10000.0f));

		oldPosX = x;
		oldPosY = y;
	} else {
		camera.changeViewPoint(x, y);
	}
}

void myIdle() {
	//timeIdle += 1;
	//cout << "run" << endl;
	//if (timeIdle == 1000) {
	//	timeIdle = 999;
	//	degree += 1;
	//}
	alpha += 0.1f;
	if (alpha > 360) alpha = 0;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(mykeyboard);
	glutMouseFunc(moseMove);
	glutMotionFunc(changeViewPoint);
	glutIdleFunc(myIdle);
	glutMainLoop();
}