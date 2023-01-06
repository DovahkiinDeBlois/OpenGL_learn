# ifndef SHADER_H
# define SHADER_H

# include <glad/glad.h> // 必须第一个引入

# include <string>
# include <fstream>
# include <sstream>
# include <iostream>

// # include "string.h"

class Shader{
private:
    /* data */
public:
    // 程序id
    unsigned int ID;
    // 路径
    static std::string dirName;

    // 构造器读取并构建着色器
    Shader(const char * vertexPath, const char * fragmentPath);

    // 使用激活程序
    void use();
    // uniform工具函数
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string name, float x, float y, float z) const;
    void setVec4(const std::string name, float r, float g, float b, float a) const;
    ~Shader();
};

# endif