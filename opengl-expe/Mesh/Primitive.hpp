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
    
    Primitive(float* vertexArray, int length, GLenum usage);
    ~Primitive();
    
    void draw();
    
    void loadVertexShader(const std::string& path, const std::string& positionName);
    void loadFragmentShader(const std::string& path, const std::string& fragName);

private:
    
    Shader m_shader;
    float* m_vertices;
    int m_length;
    GLenum m_usage;

    
};

#endif /* Primitive_hpp */
