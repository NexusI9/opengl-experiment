//
//  Primitive.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 01/09/2024.
//

#include <iostream>

#include "Primitive.hpp"
#include "../Utility/Utility.hpp"

Primitive::Primitive(float* vertexArray, int length, GLenum usage):
m_vertices(vertexArray), m_length(length), m_usage(usage){
    
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(*m_vertices) * m_length, m_vertices, m_usage);
    
    //Load Shader program
    m_shader.loadProgram();
    
    //TODO: remove, make it more maintainable
    m_shader.setVec3("triangleColor", 0.1f, 1.0f, 0.4f);
    
}

void Primitive::loadVertexShader(const std::string& path, const std::string& positionName){
    
    const char * cPath = path.c_str();
    const char * cName = positionName.c_str();
    //Compile and assign vertex shader member
    m_shader.loadVertexShader(cPath, cName);
}

void Primitive::loadFragmentShader(const std::string& path, const std::string& fragName){
    
    const char * cPath = path.c_str();
    const char * cName = fragName.c_str();
    //Compile and assign fragment shader member
    m_shader.loadFragmentShader(cPath, cName);
}

