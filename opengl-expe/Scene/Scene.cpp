//
//  Scene.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 26/09/2024.
//

#include "Scene.hpp"
#include <iostream>
#include "../Mesh/Mesh.hpp"
#include "../Utility/Debugger.hpp"


void Scene::add(GameObject* object){
    
    /** Use RTTI approach to check Object type via inheritance (downcasting)
     1. The dynamic cast function returns a nullptr if the cast fails (i.e. Object is not of target type)
     2. Need to use a pointer as argument
     3. Only works if the parent class has at least virtual method (making it polymorphic), can be the destructor
     ------
     In this case, use RTTI define the type of object and push it into respectiv vectors
     */
    
    //Assign id for later referencing (erase..)
    int id = genObjectId();
    object->ID = id;
    
    //Push to global map
    if(Mesh* meshObj = dynamic_cast<Mesh*>(object)){
        m_objects[id] = meshObj;
    }
    else{
        throw std::invalid_argument("Error while adding scene object, not a valid type");
    }
    
}

void Scene::deleteObject(int id){
    m_objects.erase( m_objects.find(id) );
}

void Scene::setCamera(Camera &camera){
    m_activeCamera = &camera;
}

void Scene::onDraw(){
    
    if(m_activeCamera){
        //Draw camera
        m_activeCamera->onDraw();
        
        //Draw objects
        for(auto& [_, object] : m_objects) object->onDraw(*m_activeCamera);
        
    }else{
        throw std::invalid_argument("No active camera where found, make sure to add at least one Camera object to the scene");
    }
    
}

void Scene::onInput(SDL_Event& event){
    
    //Update Camera input process
    if(m_activeCamera) m_activeCamera->onInput(event);
    
    //Update Objects input process
    for(int i = 0; i < m_objects.size(); i++){
        m_objects[i]->onInput(event);
    }
}

int Scene::genObjectId(int id){
    if(m_objects.find(id) != m_objects.end()) return genObjectId(++id);
    return id;
}

void Scene::showGrid(bool show){
    delete m_grid;
    if(show == true){
        Grid grid(100.0f, 100.0f);
        m_grid = grid.getMesh();
        add(m_grid);
    }
}

