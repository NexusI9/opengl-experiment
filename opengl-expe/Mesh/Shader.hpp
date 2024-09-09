//
//  Shader.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 04/09/2024.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <unordered_map>
#include <GL/glew.h>


class Shader{
   
public:
    Shader();
    ~Shader();
    
    void loadVertexShader(const char* path, const char* positionName);
    void loadFragmentShader(const char* path, const char* fragName);
    void loadProgram();
    
    GLuint loadShader(const char* shader, GLenum type);
    
    void setVec3(const std::string& name, float x, float y, float z);
    void use();
    
private:
    GLuint m_fragShader;
    GLuint m_vertShader;
    GLuint m_program;
    
    const char * m_fragName;
    const char * m_positionName;
    
    std::string getShaderLog(GLuint* shader);
    std::unordered_map<std::string, int> m_uniformsLocations;
    
    void checkUniformLocation(const std::string& name);
    
};

#endif /* Shader_hpp */
