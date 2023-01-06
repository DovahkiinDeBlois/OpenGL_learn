#include <glad/glad.h> //glad需要在一切opengl前引用
#include <GLFW/glfw3.h>
#include <iostream>
#include <string.h>

#include <cmath>

void framebuffer_size_callback(GLFWwindow * window, int width, int hight);
void processInput(GLFWwindow * window);
void color_fragmentShader1(unsigned int vertex_shader);
void color_fragmentShader2(unsigned int vertex_shader);

// 顶点着色器
const char * vertexShaderSource = "#version 330 core \n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main(){\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
    "gl_PointSize = 20.0f;\n"
    "}";

const char * fragmentShaderSource1 = "#version 330 core \n"
    "out vec4 FragColor;\n"
    "void main(){\n"
    "FragColor = vec4(0.1f, 0.2f, 0.6f, 1.0f);\n"
    "}";

const char * fragmentShaderSource2 = "#version 330 core \n"
    "out vec4 FragColor;\n"
    "void main(){\n"
    "FragColor = vec4(0.1f, 0.2f, 0.6f, 1.0f);\n"
    "}";

int main(){
    std::cout << "01_hello_world" << std::endl;
    glfwInit();
    // 设置两个版本 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 主要版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 次要版本

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //设置模式 (核心模式)

    GLFWwindow * window = glfwCreateWindow(800, 700, "马伊齐", NULL, NULL);
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

    // 定义顶点数组
    float vertices[] = {
        // -0.5f, -0.5f, 0.0f,
        // 0.5f, -0.5f, 0.0f,
        // 0.0f, tan(60), 0.0f,
        -0.5, 0.5, 0.0,
        -0.6, 0.0, 0.0,
         0.0, 0.0, 0.0,

        -0.5, 0.5, 0.0,
         0.0, 0.0, 0.0,
         0.0, 0.6, 0.0,
        
         0.0, 0.0, 0.0,
         0.0, 0.6, 0.0,
         0.3, 0.48, 0.0,

         0.3, 0.48, 0.0,
         0.52, 0.3, 0.0,
         0.0, 0.0, 0.0,

         0.3, 0.48, 0.0,
         0.52, 0.3, 0.0,
         0.5, 0.5, 0.0,

    };

    // 生成VBO 顶点缓冲对象
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &IBO);
    glBindVertexArray(VAO);
    // 绑定缓冲
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 填充数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);    

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    // 创建顶点和片段着色器(ID引用)
    unsigned int vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER); // 顶点着色器
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // 片段着色器
    // 着色器源码附加
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    glShaderSource(fragmentShader, 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShader);

    // 检测是否编译成功
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // 获取编译状态
    if(!success){
        // 获取错误信息
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    success = 0;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        // 清空char*
        memset(infoLog, '\0', sizeof(infoLog));
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    // 创建程序对象
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram(); // 过的新程序对象ID引用
    // 将着色器附加到程序对象上
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // 链接着色器
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    // 检测链接是否成功
    if(!success){
        memset(infoLog, '\0', sizeof(infoLog));
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK::COMPILATION_FAILED\n" << infoLog << std::endl;
        
    }
    // 使用着色器程序
    glUseProgram(shaderProgram);

    // glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    int time_i = 0;
    while(!glfwWindowShouldClose(window)){ // 检查是否被退出
        processInput(window); 
        // std::cout << "updata" << std::endl;
        // 渲染指令
        // ... 
        glClearColor(0.2, 0.3, 0.8, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        color_fragmentShader1(vertexShader);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawArrays(GL_TRIANGLES, 3, 3);
        glDrawArrays(GL_TRIANGLES, 6, 3);

        color_fragmentShader2(vertexShader);
        glDrawArrays(GL_TRIANGLES, 9, 3);

        glDrawArrays(GL_TRIANGLES, 12, 3);
        // glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);
        // glDrawElements(GL_POINTS, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);


        glfwSwapBuffers(window); // 交换颜色缓冲 //双缓冲交换 //与pygame同样用的双缓冲
        glfwPollEvents(); // 检查是否触发事件, 处理监听

        time_i += 1;
        if (time_i >= 300){
            time_i = 0;
        }
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &IBO);
    glDeleteProgram(shaderProgram);

    // 删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow * window, int width, int hight){
    glViewport(0,0,800,600);
}

void processInput(GLFWwindow * window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

void color_fragmentShader1(unsigned int vertex_shader){
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // 片段着色器
    glShaderSource(fragmentShader, 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShader);
    int  success;
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram(); // 过的新程序对象ID引用
    // 将着色器附加到程序对象上
    glAttachShader(shaderProgram, vertex_shader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    glAttachShader(shaderProgram, fragmentShader);
}

void color_fragmentShader2(unsigned int vertex_shader){
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // 片段着色器
    glShaderSource(fragmentShader, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader);
    int  success;
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram(); // 过的新程序对象ID引用
    // 将着色器附加到程序对象上
    glAttachShader(shaderProgram, vertex_shader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    glAttachShader(shaderProgram, fragmentShader);
}