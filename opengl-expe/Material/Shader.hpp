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
    Shader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& fragName = "outColor");
    ~Shader();
    
    void loadVertexShader(const std::string& path);
    void loadFragmentShader(const std::string& path, const std::string& fragName);
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
    
    GLint getAttributeLocation(const std::string& name){
        return glGetAttribLocation(ID, name.c_str());
    }
    
    //Uniforms Block
    void setUniformBlock(const std::string& name, GLuint bindingIndex);
    
    void use();
    
private:
    GLuint m_fragShader;
    GLuint m_vertShader;
    
    GLuint load(const std::string& path, GLenum type);
    
    std::string m_fragName;
    
    std::string getShaderLog(GLuint* shader);
    std::unordered_map<std::string, int> m_uniformsLocations;
    std::unordered_map<std::string, int> m_uniformBlocksLocations;
    
    void checkUniformLocation(const std::string& name);
    void checkUniformBlockLocation(const std::string& name);
    void checkUseProgram();
    
    static std::unordered_map<std::string, GLuint> m_shaderList;
    
};

#endif /* Shader_hpp */
