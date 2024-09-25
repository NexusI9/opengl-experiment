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
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader{
   
public:
    Shader(const char* vertexShader, const char* fragmentShader, const char *fragName);
    ~Shader();
    
    void loadVertexShader(const char* path);
    void loadFragmentShader(const char* path, const char* fragName);
    void loadProgram();
    
    GLuint ID;
    
    //Attributes
    void setAttribute(const char* attributeName, int attrNumber, int stride, void* ptr);
        
    //Uniforms
    void setVec3(const std::string& name, float x, float y, float z);
    void setVec2(const std::string& name, float x, float y);
    void setSampler2D(const std::string& name, int slot);
    void setMatrix4(const std::string& name, glm::mat4 matrix);
    
    //Uniforms Block
    void setUniformBlock(const std::string& name, GLuint bindingIndex);
    
    void use();
    
private:
    GLuint m_fragShader;
    GLuint m_vertShader;
    
    GLuint load(const char* path, GLenum type);
    
    const char * m_fragName;
    
    std::string getShaderLog(GLuint* shader);
    std::unordered_map<std::string, int> m_uniformsLocations;
    std::unordered_map<std::string, int> m_uniformBlocksLocations;
    
    void checkUniformLocation(const std::string& name);
    void checkUniformBlockLocation(const std::string& name);
    void checkUseProgram();
    
};

#endif /* Shader_hpp */
