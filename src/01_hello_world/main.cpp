#include <glad/glad.h> //glad需要在一切opengl前引用
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow * window, int width, int hight);
void processInput(GLFWwindow * window);

static bool window_updata_flage;

int main(){
    std::cout << "01_hello_world" << std::endl;
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

    GLFWwindow * window = glfwCreateWindow(800, 700, "132", NULL, NULL);
    if (window == NULL){
        std::cout << "失败" << std::endl;
        glfwTerminate();
        return  -1;
    }
    glfwMakeContextCurrent(window);

    // 给glad传入用来加载系统相关的Opengl函数指针地址得函数
    // 返回真，则成功，返回假则载入失败
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){ // proc => 步骤、程序 | address => 地址
        std::cout << "glad载入失败" << std::endl;
        return -1;
    }

    // 视口
    glViewport(0,0,800,600);

    // 注册窗口监听函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window)){ // 检查是否被退出
        processInput(window); 
        // std::cout << "updata" << std::endl;
        // 渲染指令
        // ... 
        glClearColor(0.2, 0.3, 0.8, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window); // 交换颜色缓冲 //双缓冲交换 //与pygame同样用的双缓冲
        glfwPollEvents(); // 检查是否触发事件, 处理监听

    }

    return 0;
}

void framebuffer_size_callback(GLFWwindow * window, int width, int hight){
    glViewport(0,0,800,600);
}

void processInput(GLFWwindow * window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }else if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
    }
}
