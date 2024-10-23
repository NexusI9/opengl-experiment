//
//  Camera.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 14/09/2024.
//

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.hpp"
#include "../Utility/Transform.hpp"
#include "../Utility/Constant.h"
#include "../Utility/Debugger.hpp"
#include "../Context/Keyboard.hpp"
#include "../Context/Mouse.hpp"

Camera::Camera(const CameraArgs& args):
m_fov(args.fov),
m_ratio(args.ratio),
m_nearPlane(args.nearPlane),
m_farPlane(args.farPlane),
m_matrixBindingIndex(args.bindingIndex){
    
    //init projection matrix
    updateProjectionMatrix(m_fov, m_ratio, m_nearPlane, m_farPlane);
    
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

void Camera::onDraw(){
    //Update clock
    m_clock.getDelta();
}

void Camera::onInput(SDL_Event &event){
    
    if(m_mode == Mode::DEBUGGER){
        
        //Mouse
        glm::vec2 offset = Mouse::getOffset();
        updateDirection(offset.x, offset.y);
        
        //Keyboard
        float velocity = m_speed * m_clock.getDelta();
        
        if(Keyboard::isPressed(SDLK_LSHIFT)) velocity *= 10.0f;
        
        if(Keyboard::isPressed(INPUT_FORWARD)){
            m_position -= velocity * m_front;
            translate(m_position);
        }
        if(Keyboard::isPressed(INPUT_BACKWARD)){
            m_position += velocity * m_front;
            translate(m_position);
        }
        if(Keyboard::isPressed(INPUT_LEFT)){
            m_position += velocity * glm::normalize(glm::cross(m_front, m_up));
            translate(m_position);
        }
        if(Keyboard::isPressed(INPUT_RIGHT)){
            m_position -= velocity * glm::normalize(glm::cross(m_front, m_up));
            translate(m_position);
        }
        
    }
    
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

void Camera::updateDirection(float yaw, float pitch){
    
    m_pitch += pitch;
    m_yaw += yaw;
    
    if(pitch > 89.0f) pitch = 89.0f;
    else if (pitch < -89.0f) pitch = -89.0f;

    m_direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_direction.y = sin(glm::radians(pitch));
    m_direction.z = sin(glm::radians(yaw) * cos(glm::radians(pitch)));
    m_up = glm::normalize(m_direction);
    
    //m_front *= -1;
    
    //m_view = Transform::rotate(90.0f, 1.0f, 0.0f, 0.0f);
    updateMatrixUBO();
}

