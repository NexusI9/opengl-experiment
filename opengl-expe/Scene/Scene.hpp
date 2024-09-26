//
//  Scene.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 26/09/2024.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <vector>
#include <glm/glm.hpp>

#include "./Camera.hpp"
#include "../Mesh/Gltf.hpp"



class Scene{
    
public:
    
    Scene();
    ~Scene();
    
    std::vector<Camera*> m_cameras;
    std::vector<Gltf*> m_objects;
    
    Camera* m_activeCamera;
    
    void add(BaseObject* object);
    void setActiveCamera(Camera& camera);
    
    void draw();
    
};



#endif /* Scene_hpp */
