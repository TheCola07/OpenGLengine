#include "ObjLoader.h"
#include <fstream>
#include <iostream>

#include "tgaTexture.h"

using namespace std;

Model::Model(string filename) {

	point = Vector3(0.0f, 0.0f, 0.0f);

	string line;					//�ַ�����ȡ
	fstream f;						//�ļ���
	f.open(filename, ios::in);
	if (!f.is_open()) {
		cout << "Something Went Wrong When Opening Objfiles" << endl;
	}

	while (!f.eof()) {//�����ļ���������
		getline(f, line);
		vector<string> parameters;
		string tailMark = " ";
		string ans = "";

		line = line.append(tailMark);
		for (int i = 0; i < line.length(); i++) {
			char ch = line[i];
			if (ch != ' ') {
				ans += ch;
			} else {
				if (ans == "")
					continue;
				parameters.push_back(ans);//ȡ���ַ����е�Ԫ�أ��ո���Ϊ�ָ��
				ans = "";
			}
		}
		//cout << parameters.size() << endl;
		if (parameters.size() <= 2 || parameters.size() >= 5) {
			cout << "the size is not correct" << endl;
		} else {
			if (parameters[0] == "v") {//����Ƕ���Ļ�
				vector<GLfloat> Point;
				for (int i = 1; i < 4; i++) {	//��1��ʼ���������xyz������������Ŷ����vector��(��һλΪ��ʶ��)
					GLfloat componet = atof(parameters[i].c_str());
					Point.push_back(componet);
				}
				vSets.push_back(Point);
			} else if (parameters[0] == "f") {	//�������Ļ���������������Ϊ��������������������ֵ
				vector<GLint> vIndexSets1, vIndexSets2, vIndexSets3;
				for (int i = 1; i < 4; i++) {
					string x = parameters[i];
					string a1 = "", a2 =  "", a3 = "";
					int num = 0;
					for (int j = 0; j < x.length(); j++) {//������/��
						char ch = x[j];
						if (ch != '/') {
							if (num == 0)
								a1 += ch;
							else if (num == 1)
								a2 += ch;
							else if (num == 2)
								a3 += ch;
						} else {
							num++;
							continue;
						}
					}
					GLint index = atof(a1.c_str());
					index = index--;
					vIndexSets1.push_back(index);
					index = atof(a2.c_str());
					index = index--;
					vIndexSets2.push_back(index);
					index = atof(a3.c_str());
					index = index--;
					vIndexSets3.push_back(index);
				}
				fSets.push_back(vIndexSets1);
				ftSets.push_back(vIndexSets2);
				fnSets.push_back(vIndexSets3);
			} else if (parameters[0] == "vn") {
				vector<GLfloat> vPoint;
				for (int i = 1; i < 4; i++) {
					GLfloat componet = atof(parameters[i].c_str());
					vPoint.push_back(componet);
				}
				vnSets.push_back(vPoint);
			} else if (parameters[0] == "vt") {
				//cout << "¼ȡ�ɹ�" << endl;
				vector<GLfloat> vtPoint;
				for (int i = 1; i < 3; i++) {
					GLfloat component = atof(parameters[i].c_str());
					vtPoint.push_back(component);
				}
				vtSets.push_back(vtPoint);
			}
		}
	}
	f.close();
}

void Model::DrawPoint() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myImage.texID);
	glBegin(GL_TRIANGLES);//��ʼ����
	for (int i = 0; i < fSets.size(); i++) {
		GLfloat VN[3];
		//��������
		GLfloat SV1[3];
		GLfloat SV2[3];
		GLfloat SV3[3];

		//��������ķ�����
		GLfloat SVN1[3];
		GLfloat SVN2[3];
		GLfloat SVN3[3];
		
		//�����������������
		GLfloat SVT1[2];
		GLfloat SVT2[2];
		GLfloat SVT3[2];

		if ((fSets[i]).size() != 3) {
            cout << "the fSetsets_Size is not correct" << endl;
        } else {
            GLint firstVertexIndex = (fSets[i])[0];//ȡ����������
            GLint secondVertexIndex = (fSets[i])[1];
            GLint thirdVertexIndex = (fSets[i])[2];

            SV1[0] = (vSets[firstVertexIndex])[0];//��һ������
            SV1[1] = (vSets[firstVertexIndex])[1];
            SV1[2] = (vSets[firstVertexIndex])[2];

            SV2[0] = (vSets[secondVertexIndex])[0]; //�ڶ�������
            SV2[1] = (vSets[secondVertexIndex])[1];
            SV2[2] = (vSets[secondVertexIndex])[2];

            SV3[0] = (vSets[thirdVertexIndex])[0]; //����������
            SV3[1] = (vSets[thirdVertexIndex])[1];
            SV3[2] = (vSets[thirdVertexIndex])[2];

			GLint vnfirstVertexIndex = (fnSets[i])[0];//����������
			GLint vnsecondVertexIndex = (fnSets[i])[1];
			GLint vnthirdVertexIndex = (fnSets[i])[2];

			SVN1[0] = (vnSets[vnfirstVertexIndex])[0];//��һ������
			SVN1[1] = (vnSets[vnfirstVertexIndex])[1];
			SVN1[2] = (vnSets[vnfirstVertexIndex])[2];

			SVN2[0] = (vnSets[vnsecondVertexIndex])[0]; //�ڶ�������
			SVN2[1] = (vnSets[vnsecondVertexIndex])[1];
			SVN2[2] = (vnSets[vnsecondVertexIndex])[2];

			SVN3[0] = (vnSets[vnthirdVertexIndex])[0]; //����������
			SVN3[1] = (vnSets[vnthirdVertexIndex])[1];
			SVN3[2] = (vnSets[vnthirdVertexIndex])[2];

			GLint vtfirstVertexIndex = (ftSets[i])[0];//����������
			GLint vtsecondVertexIndex = (ftSets[i])[1];
			GLint vtthirdVertexIndex = (ftSets[i])[2];

			SVT1[0] = (vtSets[vtfirstVertexIndex])[0];
			SVT1[1] = (vtSets[vtfirstVertexIndex])[1];

			SVT2[0] = (vtSets[vtsecondVertexIndex])[0];
			SVT2[1] = (vtSets[vtsecondVertexIndex])[1];

			SVT3[0] = (vtSets[vtthirdVertexIndex])[0];
			SVT3[1] = (vtSets[vtthirdVertexIndex])[1];

			//����������Ƭ
			glTexCoord2f(SVT1[0], SVT1[1]);
			glNormal3f(SVN1[0], SVN1[1], SVN1[2]);
            glVertex3f(SV1[0], SV1[1], SV1[2]);
			
			glTexCoord2f(SVT2[0], SVT2[1]);
			glNormal3f(SVN2[0], SVN2[1], SVN2[2]);
            glVertex3f(SV2[0], SV2[1], SV2[2]);
			
			glTexCoord2f(SVT3[0], SVT3[1]);
			glNormal3f(SVN2[0], SVN2[1], SVN2[2]);
            glVertex3f(SV3[0], SV3[1], SV3[2]);
			
		}
	}
	glEnd();
}

void Model::DrawFace() {

	glBegin(GL_TRIANGLES);//��ʼ����
	for (int i = 0; i < fSets.size(); i++) {
		GLfloat VN[3];
		//��������
		GLfloat SV1[3];
		GLfloat SV2[3];
		GLfloat SV3[3];

		if ((fSets[i]).size() != 3) {
			cout << "the fSetsets_Size is not correct" << endl;
		} else {
			GLint firstVertexIndex = (fSets[i])[0];//ȡ����������
			GLint secondVertexIndex = (fSets[i])[1];
			GLint thirdVertexIndex = (fSets[i])[2];

			SV1[0] = (vSets[firstVertexIndex])[0];//��һ������
			SV1[1] = (vSets[firstVertexIndex])[1];
			SV1[2] = (vSets[firstVertexIndex])[2];

			SV2[0] = (vSets[secondVertexIndex])[0]; //�ڶ�������
			SV2[1] = (vSets[secondVertexIndex])[1];
			SV2[2] = (vSets[secondVertexIndex])[2];

			SV3[0] = (vSets[thirdVertexIndex])[0]; //����������
			SV3[1] = (vSets[thirdVertexIndex])[1];
			SV3[2] = (vSets[thirdVertexIndex])[2];


			GLfloat vec1[3], vec2[3], vec3[3];//���㷨����
			//(x2-x1,y2-y1,z2-z1)
			vec1[0] = SV1[0] - SV2[0];
			vec1[1] = SV1[1] - SV2[1];
			vec1[2] = SV1[2] - SV2[2];

			//(x3-x2,y3-y2,z3-z2)
			vec2[0] = SV1[0] - SV3[0];
			vec2[1] = SV1[1] - SV3[1];
			vec2[2] = SV1[2] - SV3[2];

			//(x3-x1,y3-y1,z3-z1)
			vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
			vec3[1] = vec2[0] * vec1[2] - vec2[2] * vec1[0];
			vec3[2] = vec2[1] * vec1[0] - vec2[0] * vec1[1];

			GLfloat D = sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2));

			VN[0] = vec3[0] / D;
			VN[1] = vec3[1] / D;
			VN[2] = vec3[2] / D;

			glNormal3f(VN[0], VN[1], VN[2]);//���Ʒ�����

			glVertex3f(SV1[0], SV1[1], SV1[2]);//����������Ƭ
			glVertex3f(SV2[0], SV2[1], SV2[2]);
			glVertex3f(SV3[0], SV3[1], SV3[2]);
		}
	}
	glEnd();
}

void Model::DrawLine() {

	glBegin(GL_LINE_STRIP);//��ʼ����
	for (int i = 0; i < fSets.size(); i++) {
		GLfloat VN[3];
		//��������
		GLfloat SV1[3];
		GLfloat SV2[3];
		GLfloat SV3[3];

		if ((fSets[i]).size() != 3) {
			cout << "the fSetsets_Size is not correct" << endl;
		} else {
			GLint firstVertexIndex = (fSets[i])[0];//ȡ����������
			GLint secondVertexIndex = (fSets[i])[1];
			GLint thirdVertexIndex = (fSets[i])[2];

			SV1[0] = (vSets[firstVertexIndex])[0];//��һ������
			SV1[1] = (vSets[firstVertexIndex])[1];
			SV1[2] = (vSets[firstVertexIndex])[2];

			SV2[0] = (vSets[secondVertexIndex])[0]; //�ڶ�������
			SV2[1] = (vSets[secondVertexIndex])[1];
			SV2[2] = (vSets[secondVertexIndex])[2];

			SV3[0] = (vSets[thirdVertexIndex])[0]; //����������
			SV3[1] = (vSets[thirdVertexIndex])[1];
			SV3[2] = (vSets[thirdVertexIndex])[2];

			glVertex3f(SV1[0], SV1[1], SV1[2]);
			glVertex3f(SV2[0], SV2[1], SV2[2]);
			glVertex3f(SV3[0], SV3[1], SV3[2]);
			glVertex3f(SV1[0], SV1[1], SV1[2]);
		}
	}
	glEnd();
}

bool Model::setTexture(char* texturePath) {
	return LoadTGA(&myImage, texturePath);
}