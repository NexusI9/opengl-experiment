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

class Primitive{
    
public:
    
    Primitive(float* v, GLenum usage);
    ~Primitive();
    
    void draw();
    void loadVertexShader(const char* path, const char* outName);
    void loadFragmentShader(const char* path);

private:
    float* m_vertices;
    int m_length;
    const char* m_vertexShaderOutName;
    GLenum m_usage;
    
    GLuint m_vertexShader;
    GLuint m_fragmentShader;
    GLuint loadShader(const char* shader, GLenum type);

};

#endif /* Primitive_hpp */
