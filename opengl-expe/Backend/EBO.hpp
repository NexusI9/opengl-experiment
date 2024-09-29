//
//  EBO.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 22/09/2024.
//

#ifndef EBO_hpp
#define EBO_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <vector>


class EBO{
    
public:

    EBO();
    GLuint ID;
    
    void setData(std::vector<GLuint>& indices);
    void bind();
    void unbind();
    void remove();
    int size();
    
};

#endif /* EBO_hpp */
