//
//  Primitive.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 01/09/2024.
//

#include <iostream>

#include "Primitive.hpp"
#include "../Utility/Utility.hpp"

Primitive::Primitive(float* vertexArray,  int vertexLength, GLuint* elementArray, int elementLength):
m_vertices(vertexArray),
m_vertexLength(vertexLength),
m_elements(elementArray),
m_elementLength(elementLength){}

Primitive::~Primitive(){}

void Primitive::buffer(GLenum usage){
    
    m_usage = usage;
    
    if(m_vertices){
        //Store in VAO
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        //VERTEX ARRAY
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertexLength, m_vertices, m_usage);
    }
    
    if(m_elements){
        GLuint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_elementLength, m_elements, m_usage);
    }


    shader.loadProgram();
    
}

void Primitive::loadVertexShader(const std::string& path){
    
    const char * cPath = path.c_str();
    //Compile and assign vertex shader member
    shader.loadVertexShader(cPath);
}

void Primitive::loadFragmentShader(const std::string& path, const std::string& fragName){
    
    const char * cPath = path.c_str();
    const char * cName = fragName.c_str();
    //Compile and assign fragment shader member
    shader.loadFragmentShader(cPath, cName);
}

