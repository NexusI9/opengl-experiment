//
//  VBO.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 22/09/2024.
//

#include "UBO.hpp"

UBO::UBO(GLsizeiptr bufferSize){
    
    //Create Uniform Buffer Object
    glGenBuffers(1, &ID);
    
    //BindBuffer = bind GLuint to Target (EBO,VBO,UBO...)
    glBindBuffer(GL_UNIFORM_BUFFER, ID);
    glBufferData(GL_UNIFORM_BUFFER, bufferSize, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    //Bind to Uniform Binding Point
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, ID, 0, bufferSize);
    
}

void UBO::bind(){
    glBindBuffer(GL_UNIFORM_BUFFER, ID);
}

void UBO::unbind(){
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UBO::remove(){
    glDeleteBuffers(1, &ID);
}

