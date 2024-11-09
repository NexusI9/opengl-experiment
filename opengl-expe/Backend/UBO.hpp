//
//  VBO.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 22/09/2024.
//

#ifndef UBO_hpp
#define UBO_hpp

#include <stdio.h>
#include <GL/glew.h>

class UBO{
    
public:

    UBO(GLsizeiptr bufferSize);
    GLuint ID;

    void bind();
    void unbind();
    void remove();
    
};

#endif /* VBO_hpp */
