#include <fstream>
#include <sstream>
#include "glm/glm.hpp"
#include "Model.h"
using namespace std;

Imported::Imported() = default;

Imported::Imported(const char* filePath) {

    float x, y, z;
    ifstream fileStream(filePath, ios::in);
    string line;
    while (!fileStream.eof()) {
        getline(fileStream, line);
        if (line.compare(0, 2, "v ") == 0) {
            stringstream ss(line.erase(0, 1));
            ss >> x; ss >> y; ss >> z;
            vertVals.push_back(x);
            vertVals.push_back(y);
            vertVals.push_back(z);
        }
        if (line.compare(0, 2, "vn") == 0) {
            stringstream ss(line.erase(0, 2));
            ss >> x; ss >> y; ss >> z;
            normVals.push_back(x);
            normVals.push_back(y);
            normVals.push_back(z);
        }
        if (line.compare(0, 2, "f ") == 0) {
            string oneCorner, v, t, n;
            stringstream ss(line.erase(0, 2));
            for (int i = 0; i < 3; i++) {
                getline(ss, oneCorner, ' ');
                stringstream oneCornerSS(oneCorner);
                getline(oneCornerSS, v, '/');//��������ֵ
                getline(oneCornerSS, t, '/');//������������ֵ
                getline(oneCornerSS, n, '/');//���㷨������ֵ

                int vertRef = (stoi(v) - 1) * 3;    //��v������
                int normRef = (stoi(n) - 1) * 3;

                triangleVerts.push_back(vertVals[vertRef]);//x
                triangleVerts.push_back(vertVals[vertRef + 1]);//y
                triangleVerts.push_back(vertVals[vertRef + 2]);//z

                fnormals.push_back(normVals[normRef]);//nx
                fnormals.push_back(normVals[normRef + 1]);//ny
                fnormals.push_back(normVals[normRef + 2]);//nz
            }
        }
    }

    numVertices = (int)triangleVerts.size() / 3;//��ȡ����ĸ���

    for (int i = 0; i < numVertices; i++) {//����ͷ������㼯�ͷ���
        vertices.emplace_back(triangleVerts[i * 3], triangleVerts[i * 3 + 1], triangleVerts[i * 3 + 2]);
        normalVecs.emplace_back(fnormals[i * 3], fnormals[i * 3 + 1], fnormals[i * 3 + 2]);
    }
}

//�������в����ĸ�������
int Imported::getNumVertices() const { return numVertices; }
std::vector<glm::vec3> Imported::getVertices() { return vertices; }
std::vector<glm::vec3> Imported::getNormals() { return normalVecs; }

// ---------------------------------------------------------------