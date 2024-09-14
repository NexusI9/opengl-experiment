//
//  Transform.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 13/09/2024.
//

#ifndef Transform_hpp
#define Transform_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Transform{
  
public:
    
    static glm::mat4 translate(float x, float y, float z);
    static glm::mat4 rotate(float degree, float x, float y, float z);
    static glm::mat4 scale(float x, float y, float z);
    static glm::mat4 lookAt(glm::vec3 position, glm::vec3 target);
    
private:
    
    static constexpr glm::mat4 m_identityMatrix = glm::mat4(1.0f);
    Transform() = delete; //prevent instantiation
    
};



#endif /* Transform_hpp */
