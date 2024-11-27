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
#include "../Prefab/UI/Grid.hpp"


class Scene{
    
public:
    
    Scene() = default;
    ~Scene(){
        delete m_grid;
    };
    
    std::unordered_map<int, GameObject*> m_objects;
    
    Camera* m_activeCamera = nullptr;
    
    void add(GameObject* object);
    void setCamera(Camera& camera);
    void showGrid(bool show);
    
    void onDraw();
    void onInput(SDL_Event& event);
    
    void deleteObject(int id);
    
private:
    
    int genObjectId(int id = 0);
    Mesh* m_grid = nullptr;
    
};



#endif /* Scene_hpp */
