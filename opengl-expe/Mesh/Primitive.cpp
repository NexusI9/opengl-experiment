//
//  Primitive.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 01/09/2024.
//

#include <iostream>

#include "Primitive.hpp"
#include "Utility.hpp"

Primitive::Primitive(float* v, GLenum u):
m_vertices(v), m_usage(u){
    
}

Primitive::~Primitive(){

}

void Primitive::draw(){
    
    //VERTEX ARRAY
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, m_usage);
    
    //SHADER
    if(m_vertexShader || m_fragmentShader){
        //Create program to combine Vertex and Fragment
        GLuint shaderProgram = glCreateProgram();
        if(m_vertexShader) glAttachShader(shaderProgram, m_vertexShader);
        if(m_fragmentShader) glAttachShader(shaderProgram, m_fragmentShader);
        //Link shader program to the right vertex shader out channel (outColor1, outColor2..)
        glBindFragDataLocation(shaderProgram, 0, m_fragmentShaderOutName);
    }
    
}

void Primitive::loadVertexShader(const char* path){
    //Compile and assign vertex shader member
    m_vertexShader = loadShader(path, GL_VERTEX_SHADER);
}

void Primitive::loadFragmentShader(const char* path, const char* outName){
    //Compile and assign fragment shader member
    m_fragmentShader = loadShader(path, GL_FRAGMENT_SHADER);
    //Store vertex shader corressponding output channel
    m_fragmentShaderOutName = outName;
}

GLuint Primitive::loadShader(const char* path, GLenum type){
    
    //Import shader file
    std::string shaderString = Utility::importShader(path);
    const char* shaderFile = shaderString.c_str();
    
    std::cout << shaderFile << std::endl;
    
    //Compile Shader
    GLuint vertexShader = glCreateShader(type);
    glShaderSource(vertexShader, 1, &shaderFile, NULL);
    glCompileShader(vertexShader);
    
    //Log eventual errors
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    
    char buffer[512];
    glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
    
    if(status == 1){
        std::cout << "Successfully compiled shader: " << &shaderFile << std::endl;
    }else{
        std::cout << "Error while compilling shader: " << &shaderFile << ", check Log for more info." << std::endl;
    }
    
    return vertexShader;
    
}
