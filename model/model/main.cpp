#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <sstream>
#include "shader.h"
#include "camera.h"
#include "Model.h"
#include "stb_image.h"
#include <vector>
#include <iostream>
using namespace std;

#define numVAOs 1
#define numVBOs 3

GLuint vao[numVAOs];
GLuint vao2[numVAOs];
GLuint vbo[numVBOs];
GLuint vbo2[numVBOs];

Imported myModel("E:/openGL/�����ͼ��ѧ/�����ͼ��ѧ/Curriculumdesign1/bunny.obj");
Imported myModel2("E:/openGL/�����ͼ��ѧ/�����ͼ��ѧ/Curriculumdesign1/shuttle.obj");

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//���Ų���
float size1 = 0.3f;//��С

//ƽ�Ʋ���
float front_back = 0;
float front_back2 = 0;
float left_right = 0;
float left_right2 = 2.0;
float up_down = 0;
float up_down2 = 0;

//�߿�ͼת����־
int line_flag = 0;

// camera�ӽǱ仯�������
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();//��ʼ��GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//OpenGL���汾�� 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//OpenGL���汾�� .3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//OpenGLģʽ OpenGL����ģʽ

#ifdef __APPLE__//MacOS �±���ĵ���
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);//���ڿ��ߡ�����
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //���������̺����ĵ��ã��������ͼ��̼����ȵȡ�
    glfwMakeContextCurrent(window);//�õ�ǰ���ڵĻ����ڵ�ǰ�߳��ϳ�Ϊ��ǰ����
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//�������ڴ�С�仯
    glfwSetCursorPosCallback(window, mouse_callback);//������
    glfwSetScrollCallback(window, scroll_callback);//����
    glfwSetKeyCallback(window, key_callback);//���̼���

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("/Users/bloodsvery/Desktop/ѧϰ/�����/�����ͼ��ѧ/Curriculumdesign1/1.colors.vert", "/Users/bloodsvery/Desktop/ѧϰ/�����/�����ͼ��ѧ/Curriculumdesign1/1.colors.frag");

    // �����趨�������ݺ���
    std::vector<glm::vec3> vert = myModel.getVertices();
    std::vector<glm::vec3> norm = myModel.getNormals();
    std::vector<glm::vec3> vert2 = myModel2.getVertices();
    std::vector<glm::vec3> norm2 = myModel2.getNormals();

    std::vector<float> pvalues;
    std::vector<float> pvalues2;
    std::vector<float> nvalues;
    std::vector<float> nvalues2;

    for (int i = 0; i < myModel.getNumVertices(); i++) {
        pvalues.push_back((vert[i]).x);
        pvalues.push_back((vert[i]).y);
        pvalues.push_back((vert[i]).z);
        nvalues.push_back((norm[i]).x);
        nvalues.push_back((norm[i]).y);
        nvalues.push_back((norm[i]).z);
    }
    for (int i = 0; i < myModel2.getNumVertices(); i++) {
        pvalues2.push_back((vert2[i]).x);
        pvalues2.push_back((vert2[i]).y);
        pvalues2.push_back((vert2[i]).z);
        nvalues2.push_back((norm2[i]).x);
        nvalues2.push_back((norm2[i]).y);
        nvalues2.push_back((norm2[i]).z);
    }

    //�����ݴ��뻺����
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, pvalues.size() * 4, &pvalues[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, nvalues.size() * 4, &nvalues[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);
    //-------------------------------

    glGenVertexArrays(1, vao2);
    glBindVertexArray(vao2[0]);
    glGenBuffers(numVBOs, vbo2);

    glBindBuffer(GL_ARRAY_BUFFER, vbo2[0]);
    glBufferData(GL_ARRAY_BUFFER, pvalues2.size() * 4, &pvalues2[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo2[2]);
    glBufferData(GL_ARRAY_BUFFER, nvalues2.size() * 4, &nvalues2[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo2[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo2[2]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);    //
    glEnableVertexAttribArray(2);

    int width, height, nrChannels;
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load("/Users/bloodsvery/Desktop/ѧϰ/�����/�����ͼ��ѧ/Curriculumdesign1/sun.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data2 = stbi_load("/Users/bloodsvery/Desktop/ѧϰ/�����/�����ͼ��ѧ/Curriculumdesign1/earth.jpg", &width, &height, &nrChannels, 0);
    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data2);


    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        //�߿�ͼת�������ж�
        if (line_flag == 0) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // render
        // ------
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        auto timeControl = (float)glfwGetTime();//����timeControlϵͳʱ�亯��
        float radius = 10.0f;
        float camX = sin(timeControl) * radius;
        float camZ = cos(timeControl) * radius;//����X��Z����ʱ������Ǻ�����ʵ�ֹ�Դ����ת
        glm::vec3 lightPos(camX, 0.0f, camZ);//���ù�Դ��ά��������ת
        glm::vec3 lightPos_pro(-camX, 0.0f, -camZ);//���ù�Դ��ά��������ת

        lightingShader.use();
        lightingShader.setVec3("objectColor", 0.788f, 0.459f, 0.525f);
        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("lightPos", lightPos);
        lightingShader.setVec3("lightPos_pro", lightPos_pro);
        lightingShader.setVec3("viewPos", camera.Position);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);
        // world transformation
        glm::mat4 model = glm::mat4(1.0f);

        //����
        model = glm::scale(model, glm::vec3(size1, size1, size1));
        //ƽ��
        model = glm::translate(model, glm::vec3(left_right, up_down, front_back));
        //��ת
        lightingShader.setMat4("model", model);
        glBindVertexArray(vao[0]);
        glDrawArrays(GL_TRIANGLES, 0, myModel.getNumVertices());
        glBindTexture(GL_TEXTURE_2D, texture);

        glm::mat4 projection2 = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.3f, 100.0f);
        glm::mat4 view2 = camera.GetViewMatrix();
        lightingShader.setMat4("projection2", projection2);
        lightingShader.setMat4("view2", view2);
        // world transformation
        glm::mat4 model2 = glm::mat4(3.0f);

        //����
        model2 = glm::scale(model2, glm::vec3(size1, size1, size1));
        //ƽ��
        model2 = glm::translate(model2, glm::vec3(left_right2, up_down2, front_back2));
        //��ת
        lightingShader.setMat4("model", model2);

        glBindVertexArray(vao2[0]);
        glDrawArrays(GL_TRIANGLES, 0, myModel2.getNumVertices());
        glBindTexture(GL_TEXTURE_2D, texture2);
        glEnable(GL_DEPTH_TEST);//��Ȳ���
        glDepthFunc(GL_LEQUAL);//��ȱȽϺ��������С����ȵ�ʱ��Ҳ��Ⱦ��

        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
    }

    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = (float)xpos;
    lastY = (float)ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_Z) size1 += 0.03;//ģ�ͷŴ�

    if (key == GLFW_KEY_X) size1 -= 0.03;//ģ����С

    if (key == GLFW_KEY_F) front_back += 0.3;//ģ��ǰ��

    if (key == GLFW_KEY_G) front_back -= 0.3;//ģ�ͺ���

    if (key == GLFW_KEY_J) left_right += 0.3;//ģ������

    if (key == GLFW_KEY_H) left_right -= 0.3;//ģ������

    if (key == GLFW_KEY_K) up_down += 0.3;//ģ������

    if (key == GLFW_KEY_L) up_down -= 0.3;//ģ������

    if (key == GLFW_KEY_C) line_flag = 0;//ת��Ϊ��ͼ

    if (key == GLFW_KEY_V) line_flag = 1;//ת��Ϊ�߿�ͼ
}

//*/