//
//  Camera.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 14/09/2024.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include <glm/glm.hpp>


class Camera{

public:
    
    Camera(float fov, float ratio, float nearPlane, float farPlane);
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    glm::mat4 getCombinedMatrix();
    
    void updateProjectionMatrix(float fov, float ratio, float nearPlane, float farPlane);
    
    void lookAt(glm::vec3 position, glm::vec3 target);

private:
    
    glm::mat4 m_view;
    glm::mat4 m_projection;
    
    float m_fov;
    float m_ratio;
    float m_nearPlane;
    float m_farPlane;
    
    
};


#endif /* Camera_hpp */
