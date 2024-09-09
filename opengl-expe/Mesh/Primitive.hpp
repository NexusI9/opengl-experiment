//
//  Primitive.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 01/09/2024.
//

#ifndef Primitive_hpp
#define Primitive_hpp

#include <stdio.h>
#include <GL/glew.h>

#include "Shader.hpp"

class Primitive{
    
public:
    
    Primitive(float* v, GLenum usage);
    ~Primitive();
    
    void draw();
    
    void loadVertexShader(const char* path, const char* positionName);
    void loadFragmentShader(const char* path, const char* fragName);

private:
    
    Shader m_shader;
    float* m_vertices;
    int m_length;
    GLenum m_usage;

};

#endif /* Primitive_hpp */
