//
//  Transform.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 13/09/2024.
//

#include "Transform.hpp"


glm::mat4 Transform::translate(float x, float y, float z){
    return glm::translate(m_identityMatrix, glm::vec3(x,y,z));
}

glm::mat4 Transform::scale(float x, float y, float z){
    return glm::scale(m_identityMatrix, glm::vec3(x,y,z));
}

glm::mat4 Transform::rotate(float degree, float x, float y, float z){
    return glm::rotate(m_identityMatrix, glm::radians(degree), glm::vec3(x, y, z));
}
