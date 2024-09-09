//
//  Primitive.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 01/09/2024.
//

#include <iostream>

#include "Primitive.hpp"
#include "../Utility/Utility.hpp"

Primitive::Primitive(float* v, GLenum u):
m_vertices(v), m_usage(u){
    
}

Primitive::~Primitive(){

}

void Primitive::draw(){
    
    //Store in VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    //VERTEX ARRAY
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, m_usage);
    
    //Load Shader program
    m_shader.loadProgram();
    
}

void Primitive::loadVertexShader(const char* path, const char* positionName){
    //Compile and assign vertex shader member
    m_shader.loadVertexShader(path, positionName);
}

void Primitive::loadFragmentShader(const char* path, const char* fragName){
    //Compile and assign fragment shader member
    m_shader.loadFragmentShader(path, fragName);
}

