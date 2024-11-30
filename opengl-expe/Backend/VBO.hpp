//
//  VBO.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 22/09/2024.
//

#ifndef VBO_hpp
#define VBO_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <vector>
#include "../Mesh/Vertex.h"


class VBO{
    
public:

    VBO();
    ~VBO(){
        unbind();
    }
    
    GLuint ID;
    
    void setData(std::vector<Vertex>& vertices);
    void setData(GLsizeiptr size, const void* data, GLenum usage = GL_STATIC_DRAW);
    void copyData(GLsizeiptr size, void* data, GLenum usage = GL_STATIC_DRAW);
    void bind();
    void unbind();
    void remove();
    int size();
    
private:
    
    void* m_data = nullptr;
    void setAttributeVec3(glm::vec3 data);
    void setAttributeVec2(glm::vec3 data);
    
};

#endif /* VBO_hpp */
