//
//  Shader.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 04/09/2024.
//

#include <iostream>

#include "Shader.hpp"
#include "../Utility/Utility.hpp"


Shader::Shader(){}

Shader::~Shader(){}


GLuint Shader::load(const char* path, GLenum type){
    
    //Import shader file
    std::string shaderString = Utility::importShader(path);
    const char* shaderFile = shaderString.c_str();
    
    //Compile Shader
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderFile, NULL);
    glCompileShader(shader);
    
    //Log eventual errors
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if(status == GL_TRUE){
        std::cout << "Successfully compiled shader: " << path << std::endl;
    }else{
        std::cout << "Error while compiling shader: " << path << ", check Log below for more info.\n" << getShaderLog(&shader) << std::endl;
    }
    
    return shader;
    
}

void Shader::loadProgram(){

    if(m_vertShader || m_fragShader){
        //Create program to combine Vertex and Fragment
        m_program = glCreateProgram();
        if(m_vertShader) glAttachShader(m_program, m_vertShader);
        if(m_fragShader) glAttachShader(m_program, m_fragShader);
        
        //Attaching vertex shader out channel (outColor1, outColor2..) to shader program
        glBindFragDataLocation(m_program, 0, m_fragName);
        
        //Linking Program so can change shader during runtime
        glLinkProgram(m_program);

    }
}

std::string Shader::getShaderLog(GLuint* shader){
    
    //Retrieve error
    GLint logLength = 0;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    char log[logLength];
    glGetShaderInfoLog(*shader, logLength, NULL, log);
    
    return std::string(log);
    
}


void Shader::loadVertexShader(const char* path){
    //Compile and assign vertex shader member
    m_vertShader = load(path, GL_VERTEX_SHADER);
}

void Shader::loadFragmentShader(const char* path, const char* fragName){
    //Compile and assign fragment shader member
    m_fragShader = load(path, GL_FRAGMENT_SHADER);
    //Store vertex shader corressponding output channel
    m_fragName = fragName;
}


void Shader::checkUniformLocation(const std::string& name){
    if(m_uniformsLocations.find(name) == m_uniformsLocations.end()){
        //didn't find location, assign location to cache
        m_uniformsLocations[name] = glGetUniformLocation(m_program, (GLchar*) name.c_str());
    }
}

void Shader::checkUniformBlockLocation(const std::string& name){
    if(m_uniformBlocksLocations.find(name) == m_uniformBlocksLocations.end()){
        //didn't find location, assign location to cache
        m_uniformBlocksLocations[name] = glGetUniformBlockIndex(m_program, (GLchar*) name.c_str());
    }
}

void Shader::use(){
    glUseProgram(m_program);
}

void Shader::checkUseProgram(){
    //Automatically activate program if m_program isn't already active
    GLint activeProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &activeProgram);
    if(activeProgram != m_program) glUseProgram(m_program);
}

void Shader::setAttribute(const char *attributeName, int attrNumber, int stride, void* pointer=nullptr){
    //Shader attributes ("in") are set from the vertex array
    
    if(!m_program){
        std::cout << "No program has been found, make sure a program is loaded through the loadShader method" << std::endl;
    }
    
    //use program if not already in use;
    checkUseProgram();
    
    
    /* Create a "Generic Vertex Attribute"
     An attribute (index) taht associates an index to a shader variable
     This Generic Attribute's Index needs to be equal to our shader variable Index
     
     [Shader > "position"] <= [Generic Vertex Attribute] => [VBO] <= [VAO]
            GPU                           CPU                GPU      CPU
     
     This Generic Vertex Attribute is like a bridge that's lnking the shader to the VBO
     */
    
    GLint posAttr = glGetAttribLocation(m_program, attributeName);
    //Must enable an attribute before you can use it in a shader
    glEnableVertexAttribArray(posAttr);
    glVertexAttribPointer(posAttr, attrNumber, GL_FLOAT, GL_FALSE, stride, pointer);
}

void Shader::setVec3(const std::string &name, float x, float y, float z){
    checkUniformLocation(name);
    glUniform3f(m_uniformsLocations[name], x, y, z);
}

void Shader::setVec2(const std::string &name, float x, float y){
    checkUniformLocation(name);
    glUniform2f(m_uniformsLocations[name], x, y);
}


void Shader::setSampler2D(const std::string &name, int slot){
    checkUniformLocation(name);
    glUniform1i(m_uniformsLocations[name], slot);
}

void Shader::setMatrix4(const std::string &name, glm::mat4 matrix){
    checkUniformLocation(name);
    glUniformMatrix4fv(m_uniformsLocations[name], 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniformBlock(const std::string &name, GLuint bindingIndex){
    checkUniformBlockLocation(name);
    glUniformBlockBinding(m_program, m_uniformBlocksLocations[name], bindingIndex);
}
