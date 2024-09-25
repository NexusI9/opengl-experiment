//
//  EBO.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 22/09/2024.
//

#include "EBO.hpp"


EBO::EBO(){
    glGenBuffers(1, &ID);
}

void EBO::setData(std::vector<GLuint>& indices){
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(), GL_STATIC_DRAW);
    unbind();
}

void EBO::bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unbind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::remove(){
    glDeleteBuffers(1, &ID);
}
