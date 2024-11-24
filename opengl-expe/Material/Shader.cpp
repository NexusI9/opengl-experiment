//
//  Shader.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 04/09/2024.
//

#include <iostream>

#include "Shader.hpp"
#include "../Utility/Utility.hpp"
#include "../Utility/Debugger.hpp"


Shader::Shader(const std::string vertexShader, const std::string fragmentShader, const std::string fragName){
    loadVertexShader(vertexShader);
    loadFragmentShader(fragmentShader, fragName);
    loadProgram();
}

Shader::~Shader(){}

std::unordered_map<std::string, GLuint> Shader::m_shaderList = {};

GLuint Shader::load(const std::string path, GLenum type){
    
    if(m_shaderList.find((std::string) path) != m_shaderList.end()) return m_shaderList[(std::string) path];
    
    //Import shader file
    std::string shaderString = importFile(path.c_str());
    const char* shaderFile = shaderString.c_str();
    
    //Compile Shader
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderFile, NULL);
    glCompileShader(shader);
    
    //Log eventual errors
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if(status == GL_TRUE){
        Debugger::print("Successfully compiled shader: " + path, Verbose::Flag::SHADER);
    }else{
        Debugger::print("Error while compiling shader: " + path + ", check Log below for more info.\n" + getShaderLog(&shader), Verbose::Flag::SHADER);
    }
    
    
    m_shaderList[(std::string) path] = shader;
    return shader;
        
    
}

void Shader::loadProgram(){

    if(m_vertShader || m_fragShader){
        //Create program to combine Vertex and Fragment
        ID = glCreateProgram();
        if(m_vertShader) glAttachShader(ID, m_vertShader);
        if(m_fragShader) glAttachShader(ID, m_fragShader);
        
        //Attaching vertex shader out channel (outColor1, outColor2..) to shader program
        glBindFragDataLocation(ID, 0, m_fragName.c_str());
        
        //Linking Program so can change shader during runtime
        glLinkProgram(ID);

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


void Shader::loadVertexShader(const std::string path){
    //Compile and assign vertex shader member
    m_vertShader = load(path, GL_VERTEX_SHADER);
}

void Shader::loadFragmentShader(const std::string path, const std::string fragName){
    //Compile and assign fragment shader member
    m_fragShader = load(path, GL_FRAGMENT_SHADER);
    //Store vertex shader corressponding output channel
    m_fragName = fragName;
}


void Shader::checkUniformLocation(const std::string& name){
    if(m_uniformsLocations.find(name) == m_uniformsLocations.end()){
        //didn't find location, assign location to cache
        m_uniformsLocations[name] = glGetUniformLocation(ID, (GLchar*) name.c_str());
    }
}

void Shader::checkUniformBlockLocation(const std::string& name){
    if(m_uniformBlocksLocations.find(name) == m_uniformBlocksLocations.end()){
        //didn't find location, assign location to cache
        m_uniformBlocksLocations[name] = glGetUniformBlockIndex(ID, (GLchar*) name.c_str());
    }
}

void Shader::use(){
    glUseProgram(ID);
}

void Shader::checkUseProgram(){
    //Automatically activate program if m_program isn't already active
    GLint activeProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &activeProgram);
    if(activeProgram != ID) glUseProgram(ID);
}

void Shader::setAttribute(VAO& vao, VBO& vbo, const char *attributeName, int attrNumber, int stride, void* offset=nullptr){
    /* Create a "Generic Vertex Attribute"
     An attribute (index) taht associates an index to a shader variable
     This Generic Attribute's Index needs to be equal to our shader variable Index
     [Shader > "position"] <= glVertexAttribPointer <=[Generic Vertex Attribute] => [VBO] <= [VAO]
            GPU                                                   CPU                GPU      CPU
     This Generic Vertex Attribute is like a bridge that's lnking the Vertex Shader to the VBO
     Shader attributes ("in") are set from the vertex array
     */
    
    if(!ID){
        std::cout << "No program has been found, make sure a program is loaded using the loadShader method" << std::endl;
    }
    
    vao.bind();
    vbo.bind();
    
    GLint attrLocation = glGetAttribLocation(ID, attributeName);
    //Must enable an attribute before using it in a shader
    glVertexAttribPointer(attrLocation, attrNumber, GL_FLOAT, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(attrLocation);
    
    vao.unbind();
    vbo.unbind();
    
}

void Shader::setInt(const std::string &name, int value){
    checkUniformLocation(name);
    glUniform1i(m_uniformsLocations[name], value);
}

void Shader::setFloat(const std::string &name, float value){
    checkUniformLocation(name);
    glUniform1f(m_uniformsLocations[name], value);
}

void Shader::setVec3(const std::string &name, glm::vec3 vector){
    checkUniformLocation(name);
    glUniform3fv(m_uniformsLocations[name], 1, glm::value_ptr(vector));
}

void Shader::setVec2(const std::string &name, glm::vec2 vector){
    checkUniformLocation(name);
    glUniform2f(m_uniformsLocations[name], vector.x, vector.y);
}


void Shader::setSampler2D(const std::string &name, int slot){
    checkUniformLocation(name);
    glUniform1i(m_uniformsLocations[name], slot);
}

void Shader::setMatrix4(const std::string &name, glm::mat4 matrix){
    checkUniformLocation(name);
    glUniformMatrix4fv(m_uniformsLocations[name], 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setBoolean(const std::string &name, bool value){
    checkUniformLocation(name);
    glUniform1i(m_uniformsLocations[name], value);
}

void Shader::setUniformBlock(const std::string &name, GLuint bindingIndex){
    checkUniformBlockLocation(name);
    glUniformBlockBinding(ID, m_uniformBlocksLocations[name], bindingIndex);
}
