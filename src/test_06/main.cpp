#include <glad/glad.h> //glad需要在一切opengl前引用
#include <GLFW/glfw3.h>
#include <iostream>
#include <string.h>
#include "tool/Shader.h" // 着色器程序类

#define STB_IMAGE_IMPLEMENTATION
#include "tool/stb_image.h" // 导入纹理渲染

#include <cmath>

// practice_04
void framebuffer_size_callback(GLFWwindow * window, int width, int hight);
void processInput(GLFWwindow * window);

std::string Shader::dirName;

int main(int argc, char *argv[]){
    std::cout << "01_hello_world" << std::endl;
    Shader::dirName=argv[1];
    glfwInit();
    // 设置两个版本 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 主要版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 次要版本
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //设置模式 (核心模式)

    // 创建窗口对象
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
        //  ****位置****              ****颜色****
         0.5f,  0.5f,  0.0f,     1.0f, 0.0f, 0.0f, 0.0f,   1.0f, 1.0f, // 右上
         0.5f, -0.5f,  0.0f,     0.0f, 1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // 右下
        -0.5f, -0.5f,  0.0f,     0.0f, 0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // 左下
        -0.5f,  0.5f,  0.0f,     1.0f, 1.0f, 1.0f, 0.0f,   0.0f, 1.0f, // 左上

        // 位置                 // 颜色
        // -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f, 0.0f,   // 右下
        //  0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 1.0f, 0.0f,   // 左下
        //  0.0f, -0.5f, 0.0f,     1.0f, 0.0f, 1.0f, 0.0f,    // 顶部

    };
    unsigned int indexes[] = {
        0, 1, 3, // 第一个三角形
        1, 2, 3 // 第二个三角形
    };


    // 生成VBO 顶点缓冲对象
    unsigned int VBO, VAO, IBO;
    // 生成VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);
    // 绑定VAO缓冲对象
    glBindVertexArray(VAO);

    // 绑定VBO缓对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 填充VBO数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 绑定EBO缓对象
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    // 填充EBO数据
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

    // 设置顶点位置属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // 设置顶点颜色属性指针
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 设置渲染位置属性指针
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(7 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    // todo 加载图片
    // 生成纹理
    // unsigned int texture1, texture2;
    // glGenTextures(1, &texture1);
    // glBindTexture(GL_TEXTURE_2D, texture1);

    // // 设置环绕和过滤方式
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 图像y轴翻转
    // stbi_set_flip_vertically_on_load(true);

    // ? 宽 高 通道
    int pic_w, pic_h, nrChannels;
    // ? 图片,宽,高,通道
    // unsigned char *pic_data = stbi_load("./static/texture/container.jpg", &pic_w, &pic_h, &nrChannels, 0);
    unsigned char *pic_data = stbi_load("./static/texture/awesomeface.png", &pic_w, &pic_h, &nrChannels, 0);
    // 生成纹理
    // ? 纹理也是ID引用
    unsigned int texture; // 纹理ID定义
    glGenTextures(1, &texture); // ? 参数:纹理数量, 纹理ID
    // 纹理绑定
    glBindTexture(GL_TEXTURE_2D, texture);
    if(pic_data){
        // 纹理生成
        // parm1 纹理目标(如果是2d则与绑定的2d关联，1d与3d无影响)
        // parm2 多级渐远纹理级别
        // parm3 OpenGL纹理储存格式
        // parm4 & parm5 纹理的宽高
        // parm6 固定0（历史遗留问题）
        // parm7 源图的格式
        // parm8 源图的数据类型
        // parm9 真正的图像数据
        // return void
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pic_w, pic_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pic_data);
        // todo 为当前绑定的纹理自动生成所有需要的多级渐变纹理
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cout << "FAiled to load texture" << std::endl;
    }
    // todo 释放图像内存
    stbi_image_free(pic_data);

    ourshader.use();
    ourshader.setInt("texture1", 0);
    ourshader.setInt("texture2", 1);
    while(!glfwWindowShouldClose(window)){ // 检查是否被退出
        processInput(window); 
        // 渲染指令
        // ... 
        glClearColor(0.2, 0.3, 0.8, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        // float greenValue = (sin(timeValue) / 4.0) + 0.2f;
        // ourshader.setVec4("vColor", 0.0, greenValue, 0.0, 1.0);

        float posx = (sin(timeValue) / 2.0);
        ourshader.setFloat("offset", posx);

        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glfwSwapBuffers(window); // 交换颜色缓冲 //双缓冲交换 //与pygame同样用的双缓冲
        glfwPollEvents(); // 检查是否触发事件, 处理监听
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);

    glfwTerminate();
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
