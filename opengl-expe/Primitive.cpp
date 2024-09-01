//
//  Primitive.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 01/09/2024.
//

#include "Primitive.hpp"

Primitive::Primitive(float* v, GLenum u): m_vertices(v), m_usage(u){
    
}

Primitive::~Primitive(){

}

void Primitive::draw(){
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, m_usage);
    
    
}
