//
//  Color.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 14/10/2024.
//

#ifndef Color_h
#define Color_h

#include <glm/glm.hpp>

class Color{
  
public:
    
    static constexpr glm::vec3 Green     =   glm::vec3(0.0f, 1.0f, 0.0f);
    static constexpr glm::vec3 Blue      =   glm::vec3(0.0f, 0.0f, 1.0f);
    static constexpr glm::vec3 Red       =   glm::vec3(1.0f, 0.0f, 0.0f);
    static constexpr glm::vec3 Cyan      =   glm::vec3(0.0f, 1.0f, 1.0f);
    static constexpr glm::vec3 Yellow    =   glm::vec3(1.0f, 1.0f, 0.0f);
    static constexpr glm::vec3 Orange    =   glm::vec3(1.0f, 0.65f, 0.0f);
    static constexpr glm::vec3 Magenta   =   glm::vec3(1.0f, 0.0f, 1.0f);
    static constexpr glm::vec3 White     =   glm::vec3(1.0f, 1.0f, 1.0f);
    static constexpr glm::vec3 Black     =   glm::vec3(0.0f, 0.0f, 0.0f);
    static constexpr glm::vec3 Grey     =    glm::vec3(0.5f, 0.5f, 0.5f);
    
};

#endif /* Color_h */
