//
//  Shader.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 04/09/2024.
//

#include <iostream>

#include "Shader.hpp"
#include "../Utility/Utility.hpp"


Shader::Shader(){}

Shader::~Shader(){}


GLuint Shader::loadShader(const char* path, GLenum type){
    
    //Import shader file
    std::string shaderString = Utility::importShader(path);
    const char* shaderFile = shaderString.c_str();
    
    //Compile Shader
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderFile, NULL);
    glCompileShader(shader);
    
    //Log eventual errors
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if(status == GL_TRUE){
        std::cout << "Successfully compiled shader: " << &shaderFile << std::endl;
    }else{
        std::cout << "Error while compiling shader: " << &shaderFile << ", check Log below for more info.\n" << getShaderLog(&shader) << std::endl;
    }
    
    return shader;
    
}

void Shader::loadProgram(){
    //SHADER
    if(m_vertShader || m_fragShader){
        //Create program to combine Vertex and Fragment
        GLuint shaderProgram = glCreateProgram();
        if(m_vertShader) glAttachShader(shaderProgram, m_vertShader);
        if(m_fragShader) glAttachShader(shaderProgram, m_fragShader);
        
        //Link shader program to the right vertex shader out channel (outColor1, outColor2..)
        glBindFragDataLocation(shaderProgram, 0, m_fragName);
    }
}

std::string Shader::getShaderLog(GLuint* shader){
    
    //Retrieve error
    GLint logLength = 0;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    char log[logLength];
    glGetShaderInfoLog(*shader, logLength, NULL, log);
    
    return std::string(log);
    
}


void Shader::loadVertexShader(const char* path){
    //Compile and assign vertex shader member
    m_vertShader = loadShader(path, GL_VERTEX_SHADER);
}

void Shader::loadFragmentShader(const char* path, const char* fragName){
    //Compile and assign fragment shader member
    m_fragShader = loadShader(path, GL_FRAGMENT_SHADER);
    //Store vertex shader corressponding output channel
    m_fragName = fragName;
}

