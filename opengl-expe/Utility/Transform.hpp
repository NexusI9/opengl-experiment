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
    static glm::mat4 lookAt(glm::vec3 position, glm::vec3 target, glm::vec3 up = glm::vec3(0.0f,0.0f,0.0f));
    
private:
    
    /**
            Use and 4x4 identity Matrix to translate Vector3 to Mat4 so easier to combine and multiply in vertex shader
     */
    static constexpr glm::mat4 m_identityMatrix = glm::mat4(1.0f);
    Transform() = delete; //prevent instantiation
    
};



#endif /* Transform_hpp */
