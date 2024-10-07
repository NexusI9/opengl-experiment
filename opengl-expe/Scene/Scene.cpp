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

void Scene::add(GameObject* object){
    
    /** Use RTTI approach to check Object type via inheritance (downcasting)
     1. The dynamic cast function returns a nullptr if the cast fails (i.e. Object is not of target type)
     2. Need to use a pointer as argument
     3. Only works if the parent class has at least virtual method (making it polymorphic), can be the destructor
     ------
     In this case, use RTTI define the type of object and push it into respectiv vectors
     */
    
    if(Mesh* meshObj = dynamic_cast<Mesh*>(object)){
        m_objects.push_back(meshObj);
    }
    if(MeshGroup* groupObj = dynamic_cast<MeshGroup*>(object)){
        m_objects.push_back(groupObj);
    }else{
        throw std::invalid_argument("Error while adding scene object, not a valid type");
    }
    
}

void Scene::setCamera(Camera &camera){
    m_activeCamera = &camera;
}

void Scene::draw(){
    
    if(m_activeCamera){
        for(auto& object : m_objects){
            object->draw(*m_activeCamera);
        }
    }else{
        throw std::invalid_argument("No active camera where found, make sure to add at least one Camera object to the scene");
    }

    
}

