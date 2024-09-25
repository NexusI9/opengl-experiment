//
//  VAO.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 22/09/2024.
//

#include "VAO.hpp"


VAO::VAO(){
    glGenVertexArrays(1, &ID);
}


void VAO::bind(){
    glBindVertexArray(ID);
}

void VAO::unbind(){
    glBindVertexArray(0);
}

void VAO::remove(){
    glDeleteVertexArrays(1, &ID);
}
