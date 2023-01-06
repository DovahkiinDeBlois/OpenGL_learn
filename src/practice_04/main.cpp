#include <glad/glad.h> //glad需要在一切opengl前引用
#include <GLFW/glfw3.h>
#include <iostream>
#include <string.h>
#include "tool/Shader.h"

#include <cmath>

// practice_04
void framebuffer_size_callback(GLFWwindow * window, int width, int hight);
void processInput(GLFWwindow * window);

std::string Shader::dirName;
// // 顶点着色器
// const char * vertexShaderSource = "#version 330 core \n"
//     "layout (location = 0) in vec3 aPos;\n"
//     // "layout (location = 1) in vec4 aColor;\n"
//     "uniform float offset;\n "
//     // "out vec4 vColor;\n"
//     "void main(){\n"
//     "gl_Position = vec4(aPos.x + offset, aPos.y + offset, aPos.z + offset, 1.0f);\n"
//     // "vColor = vec4(-aPos.x, -aPos.y, aPos.z, 1.0);\n"
//     // "vColor = vec4(0.0f, 0.2f, 0.7f, 1.0f);\n"
//     // "vColor = vec4(aColor);\n"
//     "gl_PointSize = 20.0f;\n"
//     "}";

// const char * fragmentShaderSource = "#version 330 core \n"
//     "out vec4 FragColor;\n"
//     // "in vec4 vColor;\n"
//     "uniform vec4 vColor;\n"
//     "void main(){\n"
//     "FragColor = vec4(vColor);\n"
//     // "FragColor = vec4(vColor);"
//     "}";
// const char * fragmentShaderSource2 = "#version 330 core \n"
//     "out vec4 FragColor;\n"
//     "in vec4 vColor;"
//     "void main(){\n"
//     // "FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);"
//     "FragColor = vec4(1.0f, 1.0f, (vColor.g+0.3)*1.6, 1.0f);"
//     // "FragColor = vec4(vColor);"
//     "}";

int main(int argc, char *argv[]){
    std::cout << "01_hello_world" << std::endl;
    Shader::dirName=argv[1];
    glfwInit();
    // 设置两个版本 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 主要版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 次要版本
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //设置模式 (核心模式)

    // 创建窗口对象
    // GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL); // 宽，高，标题
    // if (window == NULL)
    // {
    //     std::cout << "Failed to create GLFW window" << std::endl;
    //     glfwTerminate();
    //     return -1;
    // }
    // glfwMakeContextCurrent(window);

    GLFWwindow * window = glfwCreateWindow(800, 700, "practic_04", NULL, NULL);
    if (window == NULL){
        std::cout << "失败" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 给glad传入用来加载系统相关的Opengl函数指针地址得函数
    // 返回真，则成功，返回假则载入失败
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){ // proc => 步骤、程序 | address => 地址
        std::cout << "glad载入失败" << std::endl;
        return -1;
    }

    // 视口
    glViewport(0,0,800,800);
    glEnable(GL_PROGRAM_POINT_SIZE);

    // 注册窗口监听函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader ourshader("./shader/vertex.glsl", "./shader/fragment.glsl");

    // 定义顶点数组
    GLfloat vertices[] = {
        // 位置                 // 颜色
         0.5f, -0.5f,  0.0f,     1.0f, 0.0f, 0.0f, 0.0f,   // 右下
        -0.5f, -0.5f,  0.0f,     0.0f, 1.0f, 0.0f, 0.0f,   // 左下
         0.0f,  0.5f,  0.0f,     0.0f, 0.0f, 1.0f, 0.0f,    // 顶部

        // 位置                 // 颜色
        // -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f, 0.0f,   // 右下
        //  0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 1.0f, 0.0f,   // 左下
        //  0.0f, -0.5f, 0.0f,     1.0f, 0.0f, 1.0f, 0.0f,    // 顶部

    };
    // unsigned int indexes[] = {
    //     0, 1, 3, // 第一个三角形
    //     1, 2, 3 // 第二个三角形
    // };


    // 生成VBO 顶点缓冲对象
    unsigned int VBO, VAO, IBO;
    // 生成VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // 绑定VAO缓冲对象
    glBindVertexArray(VAO);

    // 绑定VBO缓对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 填充VBO数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 设置顶点位置属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // 设置顶点颜色属性指针
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    ourshader.use();
    while(!glfwWindowShouldClose(window)){ // 检查是否被退出
        processInput(window); 
        // 渲染指令
        // ... 
        glClearColor(0.2, 0.3, 0.8, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 4.0) + 0.2f;
        float posx = (sin(timeValue) / 2.0);

        ourshader.setFloat("offset", posx);
        ourshader.setVec4("vColor", 0.0, greenValue, 0.0, 1.0);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window); // 交换颜色缓冲 //双缓冲交换 //与pygame同样用的双缓冲
        glfwPollEvents(); // 检查是否触发事件, 处理监听
    }

    return 0;
}

void framebuffer_size_callback(GLFWwindow * window, int width, int hight){
    glViewport(0,0,width,hight);
}

void processInput(GLFWwindow * window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}
