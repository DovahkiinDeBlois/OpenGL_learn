#include <glad/glad.h> //glad需要在一切opengl前引用
#include <GLFW/glfw3.h>
#include <iostream>
#include <string.h>

#include <cmath>

void framebuffer_size_callback(GLFWwindow * window, int width, int hight);
void processInput(GLFWwindow * window);

// 顶点着色器
const char * vertexShaderSource = "#version 330 core \n"
    "layout (location = 0) in vec3 aPos;\n"
    "out vec4 vColor;\n"
    "void main(){\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
    "vColor = vec4(-aPos.x, -aPos.y, aPos.z, 1.0);\n"
    // "vColor = vec4(0.0f, 0.2f, 0.7f, 1.0f);\n"
    "gl_PointSize = 20.0f;\n"
    "}";

const char * fragmentShaderSource1 = "#version 330 core \n"
    "out vec4 FragColor;\n"
    "in vec4 vColor;\n"
    "void main(){\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
    "FragColor = vec4(vColor);"
    "}";
const char * fragmentShaderSource2 = "#version 330 core \n"
    "out vec4 FragColor;\n"
    "in vec4 vColor;"
    "void main(){\n"
    // "FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);"
    "FragColor = vec4(1.0f, 1.0f, (vColor.g+0.3)*1.6, 1.0f);"
    // "FragColor = vec4(vColor);"
    "}";

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
    glEnable(GL_PROGRAM_POINT_SIZE);

    // 注册窗口监听函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 定义顶点数组
    GLfloat vertices[] = {
        -0.75, -0.5, 0.0,
        -0.25, -0.5, 0.0,
        -0.5, 0.5, 0.0,

        0.75, -0.5, 0.0,
        0.25, -0.5, 0.0,
        0.5, 0.5, 0.0,
        
    };
    unsigned int indexes[] = {
        0, 1, 3, // 第一个三角形
        1, 2, 3 // 第二个三角形
    };

    // 生成VBO 顶点缓冲对象
    // EBO == IBO, IBO就是索引缓冲对象 index buffer object
    unsigned int VBOs[2], VAOs[2], IBO;
    glGenBuffers(2, VBOs);
    // 生成VBO
    glGenVertexArrays(2, VAOs);

    // 绑定缓冲
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    // 填充数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 链接顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void *) 0);
    // 启用顶点属性；顶点属性默认是禁用的。
    glEnableVertexAttribArray(0);

    // 绑定缓冲
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    // 填充数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 链接顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void *) (9*sizeof(float)));
    // 启用顶点属性；顶点属性默认是禁用的。
    glEnableVertexAttribArray(0);

    // IBO应当在VAO绑定后食用
    glGenBuffers(1, &IBO);
    // 绑定IBO缓冲
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    // 填充IBO数据
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);


    // 不知道这句什么意思，和上面的就是单词调换了位置，不得不承认，opengl学习起来确实很有难度
    // glEnableVertexArrayAttrib();

    // VAO解绑
    glBindVertexArray(0);

    // 创建顶点和片段着色器(ID引用)
    unsigned int vertexShader, fragmentShader1, fragmentShader2;
    vertexShader = glCreateShader(GL_VERTEX_SHADER); // 顶点着色器
    fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER); // 片段着色器
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER); // 片段着色器
    // 着色器源码附加
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShader1);

    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

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
    glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
    if(!success){
        // 清空char*
        memset(infoLog, '\0', sizeof(infoLog));
        glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    // 创建程序对象
    unsigned int shaderProgram1, shaderProgram2;
    shaderProgram1 = glCreateProgram(); // 过的新程序对象ID引用
    shaderProgram2 = glCreateProgram(); // 过的新程序对象ID引用
    // 将着色器附加到程序对象上
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    // 将着色器附加到程序对象上
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);

    // 链接着色器
    glLinkProgram(shaderProgram1);
    glLinkProgram(shaderProgram2);
    glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
    // 检测链接是否成功
    if(!success){
        memset(infoLog, '\0', sizeof(infoLog));
        glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK::COMPILATION_FAILED\n" << infoLog << std::endl;
        
    }
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    // 检测链接是否成功
    if(!success){
        memset(infoLog, '\0', sizeof(infoLog));
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK::COMPILATION_FAILED\n" << infoLog << std::endl;
        
        return -1;
    }
    // // 使用着色器程序
    // glUseProgram(shaderProgram1);

    // // 删除着色器对象
    // glDeleteShader(fragmentShader1);

    
    int time_i = 0;
    while(!glfwWindowShouldClose(window)){ // 检查是否被退出
        processInput(window); 
        // 渲染指令
        // ... 
        glClearColor(0.2, 0.3, 0.8, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        // 使用程序（着色器程序）
        glUseProgram(shaderProgram1);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glDeleteShader(fragmentShader1);
        
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glDeleteShader(fragmentShader2);


        glfwSwapBuffers(window); // 交换颜色缓冲 //双缓冲交换 //与pygame同样用的双缓冲
        glfwPollEvents(); // 检查是否触发事件, 处理监听
        // time_i += 1;
        // if (time_i >= 3000){
        //     time_i = 0;
        // }
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
