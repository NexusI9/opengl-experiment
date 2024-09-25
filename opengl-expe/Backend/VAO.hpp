//
//  VAO.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 22/09/2024.
//

#ifndef VAO_hpp
#define VAO_hpp

#include <stdio.h>
#include <GL/glew.h>

class VAO{
    
public:
    VAO();
    GLuint ID;
    
    void bind();
    void unbind();
    void remove();
    
};

#endif /* VAO_hpp */
