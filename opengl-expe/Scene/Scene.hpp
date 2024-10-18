//
//  Scene.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 26/09/2024.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <unordered_map>
#include <glm/glm.hpp>

#include "./Camera.hpp"
#include "./GameObject.h"


class Scene{
    
public:
    
    Scene();
    ~Scene();
    
    std::unordered_map<int, GameObject*> m_objects;
    
    Camera* m_activeCamera = nullptr;
    
    void add(GameObject* object);
    void setCamera(Camera& camera);
    void displayGrid(bool display);
    
    void draw();
    void erase(int id);
    
private:
    
    int genObjectId(int id = 0);
    
};



#endif /* Scene_hpp */
