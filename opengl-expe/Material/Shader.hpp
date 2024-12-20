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
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Backend/VAO.hpp"
#include "../Backend/VBO.hpp"


class Shader{
   
public:
    Shader(const char* vertexShader, const char* fragmentShader, const char *fragName);
    ~Shader();
    
    void loadVertexShader(const char* path);
    void loadFragmentShader(const char* path, const char* fragName);
    void loadProgram();
    
    GLuint ID;
    
    //Attributes
    void setAttribute(VAO& vao, VBO& vbo, const char* attributeName, int attrNumber, int stride, void* offset);
        
    //Uniforms
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    
    void setVec3(const std::string& name, glm::vec3 vector);
    void setVec2(const std::string& name, glm::vec2 vector);
    
    void setSampler2D(const std::string& name, int slot);
    
    void setMatrix4(const std::string& name, glm::mat4 matrix);
    
    void setBoolean(const std::string& name, bool value);
    
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
    
    static std::unordered_map<std::string, GLuint> m_shaderList;
    
};

#endif /* Shader_hpp */
