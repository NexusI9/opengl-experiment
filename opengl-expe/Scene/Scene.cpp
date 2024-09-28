//
//  Scene.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 26/09/2024.
//

#include "Scene.hpp"
#include <iostream>


Scene::Scene(){}
Scene::~Scene(){}

void Scene::add(BaseObject* object){
    
    /** Use RTTI approach to check Object type via inheritance (downcasting)
     1. The dynamic cast function returns a nullptr if the cast fails (i.e. Object is not of target type)
     2. Need to use a pointer as argument
     3. Only works if the parent class has at least virtual method (making it polymorphic), can be the destructor
     ------
     In this case, use RTTI define the type of object and push it into respectiv vectors
     */
    
    if(Gltf* gltfObj = dynamic_cast<Gltf*>(object)) m_objects.push_back(gltfObj);
    else if(Rectangle* rectObj = dynamic_cast<Rectangle*>(object)) m_rectangles.push_back(rectObj);
    else if (Camera* camObj = dynamic_cast<Camera*>(object)) {
        m_cameras.push_back(camObj);
        //Define new camera as default if no camera
        if(m_activeCamera == nullptr) m_activeCamera = camObj;
    }else{
        throw std::invalid_argument("Error while adding scene object, not a valid type");
    }
    
}

void Scene::draw(){
    
    if(m_activeCamera){
        for(auto& object : m_objects){
            object->draw(*m_activeCamera);
        }
        
        for(auto& object : m_rectangles){
            object->draw(*m_activeCamera);
        }
    }

    
}

