# include "shader.h"

Shader::Shader(const char * vertexPath, const char * fragmentPath){
    // 1、从文件路径中获取顶点片段着色器
    // todo 读取文件作为字符串
    std::string vertexCode;
    std::string fragmentCode;
    // todo 读文件对象
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // todo 定义非const变量操作
    // std::string vert_string = vertexPath
    // std::string frag_string
    // todo 将相对路径合称为绝对路径
    std::string absolute_path_vert = std::string(vertexPath).insert(2, this->dirName);
    std::string absolute_path_frag = std::string(fragmentPath).insert(2, this->dirName);

    // 保证ifstream对象可以抛出异常
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try{
        vShaderFile.open(absolute_path_vert.data());
        fShaderFile.open(absolute_path_frag.data());

        std::stringstream vShaderStream, fShaderStream;
        // 读取文件的缓冲内容到数据流中
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // 关闭文件处理器
        vShaderFile.close();
        fShaderFile.close();
        // 转换数据流到string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        
    }catch(std::ifstream::failure e){
        // char error_info[128];
        // error_info = e.what();
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ::" << e.what() << std::endl;
    }
    std::cout << "Read the glsl file successfully!" << std::endl;
    
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();


    // 2.编译着色器
    unsigned int vertex,fragment;

    int success;
    char infoLog[512];

    // 顶点着色器
    vertex = glCreateShader(GL_VERTEX_SHADER);
    // 着色器源码附加
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    // 着色器编译
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success); // 获取编译状态
    if(!success){
        // 获取错误信息
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return ;
    }

    // 片段着色器
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return ;
    }

    // 着色器程序
    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertex);
    glAttachShader(this->ID, fragment);
    glLinkProgram(this->ID);
    
    glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use(){
    glUseProgram(this->ID);
}

void Shader::setBool(const std::string &name, bool value) const{
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value); 
}
void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setVec3(const std::string name, float x, float y, float z) const{
    glUniform3f(glGetUniformLocation(this->ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string name, float r, float g, float b, float a) const{
    glUniform4f(glGetUniformLocation(this->ID, name.c_str()), r, g, b, a);
}

Shader::~Shader(){
}

