//
//  Camera.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 14/09/2024.
//

#include <glm/gtc/matrix_transform.hpp>

#include "Camera.hpp"
#include "../Utility/Transform.hpp"

Camera::Camera(float fov, float ratio, float nearPlane, float farPlane):
m_fov(fov), m_ratio(ratio), m_nearPlane(nearPlane), m_farPlane(farPlane){
    //init projection matrix
    updateProjectionMatrix(fov, ratio, nearPlane, farPlane);
    //init position
    lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    
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
    m_view = Transform::lookAt(position, target);
}
