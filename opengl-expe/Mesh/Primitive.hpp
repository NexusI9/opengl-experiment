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
#include "Texture.hpp"

class Primitive{
    
public:
    
    Primitive(float* vertexArray,  int vertexLength, GLuint* elementArray, int elementLength);
    ~Primitive();
    
    void buffer(GLenum usage);
    
    void loadShader(const std::string& vertShader, const std::string& fragShader, const std::string& fragName);
    
    void loadTexture(const std::string& path, const int width, const int height);
    
    Shader* shader = nullptr;
    Texture* texture = nullptr;
    

private:
    
    float* m_vertices;
    int m_vertexLength;
    
    GLuint* m_elements;
    int m_elementLength;
    
    GLenum m_usage;

    
};

#endif /* Primitive_hpp */
