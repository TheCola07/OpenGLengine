#include <vector>
#include <glm/glm.hpp>

class Imported
{
private:
    int numVertices{};//��ŵ�ĸ���
    std::vector<glm::vec3> vertices;//��Ŷ��㼯
    std::vector<glm::vec3> normalVecs;//��ŷ���
    std::vector<float> vertVals;//��Ŷ���ĵ��ֵ
    std::vector<float> triangleVerts;//��Ű�������������Ķ��㼯
    std::vector<float> fnormals;//��Ű�������������ķ���
    std::vector<float> normVals;//��ŷ����ֵ
public:
    Imported();//�޲ι��죬��ûʲô��
    Imported(const char* filePath);//�ļ������죬���䱾��ģ��
    int getNumVertices() const;//���ض�������ĺ���
    std::vector<glm::vec3> getVertices();//���ض��㼯vertices�ĺ���
    std::vector<glm::vec3> getNormals();//���ط���normalVecs�ĺ���
};
