//
//  VBO.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 22/09/2024.
//

#include "VBO.hpp"

VBO::VBO(){
    glGenBuffers(1, &ID);
}

void VBO::setData(std::vector<Vertex> &vertices){
    bind();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    unbind();
}

void VBO::bind(){
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::remove(){
    glDeleteBuffers(1, &ID);
}

int VBO::size(){
    
    glBindBuffer(GL_ARRAY_BUFFER, ID);

    // Get size parameter.
    int32_t bsize = 0;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bsize);
    
    // Unbind VBO.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    return bsize;
}
