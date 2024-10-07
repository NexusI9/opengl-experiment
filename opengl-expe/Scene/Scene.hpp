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
#include "../Mesh/Mesh.hpp"
#include "../Mesh/MeshGroup.hpp"

class Scene{
    
public:
    
    Scene();
    ~Scene();
    
    std::vector<GameObject*> m_objects;
    
    Camera* m_activeCamera = nullptr;
    
    void add(GameObject* object);
    void setCamera(Camera& camera);
    
    void draw();
    
};



#endif /* Scene_hpp */
