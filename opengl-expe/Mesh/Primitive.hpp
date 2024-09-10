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
    
    Primitive(float* vertexArray,  int vertexLength, GLuint* elementArray, int elementLength, GLenum usage);
    ~Primitive();
    
    void buffer();
    
    void loadVertexShader(const std::string& path);
    void loadFragmentShader(const std::string& path, const std::string& fragName);
    
    Shader shader;

private:
    
    float* m_vertices;
    int m_vertexLength;
    
    GLuint* m_elements;
    int m_elementLength;
    
    GLenum m_usage;

    
};

#endif /* Primitive_hpp */
