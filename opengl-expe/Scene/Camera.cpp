//
//  Camera.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 14/09/2024.
//

#include <glm/gtc/matrix_transform.hpp>

#include "Camera.hpp"
#include "../Utility/Transform.hpp"
#include <iostream>

Camera::Camera(float fov, float ratio, float nearPlane, float farPlane, GLuint bindingIndex):
m_fov(fov),
m_ratio(ratio),
m_nearPlane(nearPlane),
m_farPlane(farPlane),
m_matrixBindingIndex(bindingIndex){
    
    //init projection matrix
    updateProjectionMatrix(fov, ratio, nearPlane, farPlane);
    
    //init position
    //lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    
    //Create Uniform Buffer Object
    glGenBuffers(1, &m_matrixUBO);
    //BindBuffer = bind GLuint to Target (EBO,VBO,UBO...)
    glBindBuffer(GL_UNIFORM_BUFFER, m_matrixUBO);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    //Bind to Uniform Binding Point
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_matrixUBO, 0, 2 * sizeof(glm::mat4));
    
    updateMatrixUBO();
    
}

void Camera::updateProjectionMatrix(float fov, float ratio, float nearPlane, float farPlane){
    
    m_fov = glm::radians(fov);
    m_ratio = ratio;
    m_nearPlane = nearPlane;
    m_farPlane = farPlane;
    
    m_projection = glm::perspective(m_fov, m_ratio, m_nearPlane, m_farPlane);
    
}



glm::mat4 Camera::getViewMatrix(){
    return m_view;
}

glm::mat4 Camera::getProjectionMatrix(){
    return m_projection;
}

glm::mat4 Camera::getCombinedMatrix(){
    return  m_projection * m_view;
}

void Camera::lookAt(glm::vec3 position, glm::vec3 target){
    m_position = position;
    m_view = Transform::lookAt(position, target);
    updateMatrixUBO();
}

void Camera::translate(glm::vec3 position){
    m_position = position;
    m_view = Transform::translate(position.x, position.y, position.z);
    updateMatrixUBO();
}

GLuint Camera::getMatrixUBO(){
    return m_matrixUBO;
}

GLuint Camera::getMatrixBindingIndex(){
    return m_matrixBindingIndex;
}

void Camera::updateMatrixUBO(){
    
    glBindBuffer(GL_UNIFORM_BUFFER, m_matrixUBO);
    
    //Store view matrix
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(m_view));
    
    //Store projection matrix
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(m_projection));

    
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
}
