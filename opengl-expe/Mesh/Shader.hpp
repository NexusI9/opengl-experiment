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
    
    void loadVertexShader(const char* path);
    void loadFragmentShader(const char* path, const char* fragName);
    void loadProgram();
    
    GLuint load(const char* shader, GLenum type);
    void setAttributeFromBuffer(const char* attributeName, int attrNumber, int stride, void* ptr);
        
    void setVec3(const std::string& name, float x, float y, float z);
    void setVec2(const std::string& name, float x, float y);
    void setSampler2D(const std::string& name, int slot);
    void use();
    
private:
    GLuint m_fragShader;
    GLuint m_vertShader;
    GLuint m_program;
    
    const char * m_fragName;
    
    std::string getShaderLog(GLuint* shader);
    std::unordered_map<std::string, int> m_uniformsLocations;
    
    void checkUniformLocation(const std::string& name);
    void checkUseProgram();
    
};

#endif /* Shader_hpp */
