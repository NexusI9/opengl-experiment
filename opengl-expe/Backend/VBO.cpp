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

void VBO::setData(std::vector<Vertex>& vertices){
    bind();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    unbind();
}

/**
 Set buffer from data pointer, meaning if data goes out of scope, buffer data won't be valid, hence the alloc method that stores the data ownership into the buffer
 */
void VBO::setData(GLsizeiptr size, const void* data, GLenum usage){    
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    unbind();
}

/**
 Transfert a copy of data into the buffer as to make it peristent through the buffer life instead of the buffer itself
 */
void VBO::copyData(GLsizeiptr size, void* source, GLenum usage){
    m_data = malloc(size);
    if(m_data == nullptr) throw std::bad_alloc();
    memcpy(m_data, source, size);
    
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, m_data, usage);
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
