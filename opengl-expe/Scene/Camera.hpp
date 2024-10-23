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
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "../Utility/Clock.hpp"

struct CameraArgs{
    float fov = 45.0f;
    float ratio = (float) 1920/1080;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    GLuint bindingIndex = 0;
};


class Camera{

public:
    
    enum class Mode{
        DEBUGGER,
        BUILD,
        PLAYER
    };
    
    Camera(const CameraArgs& args);
    ~Camera(){};

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    glm::mat4 getCombinedMatrix();
    glm::vec3 getPosition(){
        return m_position;
    };
    
    void setPosition();
    
    void onInput(SDL_Event& event);
    void onDraw();
    
    void updateProjectionMatrix(float fov, float ratio, float nearPlane, float farPlane);
    
    void lookAt(glm::vec3 position, glm::vec3 target);
    void translate(glm::vec3 position);
    void rotate(glm::vec3 rotation);
    
    GLuint getMatrixUBO();
    GLuint getMatrixBindingIndex();

private:
    
    glm::mat4 m_view = glm::mat4(1.0f);
    glm::mat4 m_projection = glm::mat4(1.0f);
    glm::vec3 m_position = glm::vec3(0.0f);
    glm::vec3 m_rotation = glm::vec3(0.0f);
    
    
    glm::vec3 m_target = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 m_direction = glm::vec3(0.0f);
    
    glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_right = glm::normalize(glm::cross(m_front, m_up));
    
    float m_yaw;
    float m_pitch;
    
    float m_speed = 8.0f;
    
    Mode m_mode = Mode::DEBUGGER;
    
    float m_fov;
    float m_ratio;
    float m_nearPlane;
    float m_farPlane;
    GLuint m_matrixUBO;
    GLuint m_matrixBindingIndex;
    
    void updateMatrixUBO();
    void updateDirection(float yaw, float pitch);
    
    Clock m_clock;
    
};


#endif /* Camera_hpp */
