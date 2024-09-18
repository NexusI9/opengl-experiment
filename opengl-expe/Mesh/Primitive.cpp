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

Primitive::~Primitive(){
    delete shader;
    delete texture;
}

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

    
}

void Primitive::loadShader(const std::string& vertShader, const std::string& fragShader, const std::string& fragName){
    
    shader = new Shader();
    
    const char* cVertShader = vertShader.c_str();
    //Compile and assign vertex shader member
    shader->loadVertexShader(cVertShader);
    
    const char* cFragShader = fragShader.c_str();
    const char* cFragName = fragName.c_str();
    //Compile and assign fragment shader member
    shader->loadFragmentShader(cFragShader, cFragName);
    shader->loadProgram();
}

void Primitive::loadTexture(const std::string& path, const int width, const int height, const int slot){
    
    texture = new Texture(path, width, height, slot);
    texture->load();
    
}


