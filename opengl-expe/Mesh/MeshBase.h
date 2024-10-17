//
//  MeshBase.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 09/10/2024.
//

#ifndef MeshBase_h
#define MeshBase_h

#include "../Scene/GameObject.h"
#include "../Scene/Scene.hpp"
#include"../Material/MaterialBase.hpp"
#include <glm/glm.hpp>

class MeshBase : public GameObject{
    
public:
    
    MeshBase() : GameObject(Type::OBJECT){};
    
    enum class DrawMode{
        DEFAULT,
        WIREFRAME,
        DEBUGGER,
        POINTS
    };
    
    virtual void setMaterial(MaterialBase& material) = 0;
    virtual void setDrawMode(DrawMode mode) = 0;
    
    virtual void setPosition(float x, float y, float z) = 0;
    virtual void setScale(float x, float y, float z) = 0;
    virtual void setRotation(float degree, float x, float y, float z) = 0;
    virtual void lookAt(float x, float y, float z) = 0;
    
    glm::vec3 getPosition(){
        return m_position;
    }
    
    glm::vec3  getScale(){
        return m_scale;
    }
    
    glm::vec3  getRotation(){
        return m_rotation;
    }
    
    glm::mat4 getModelMatrix(){
        return m_modelMatrix;
    }
    
    void setModelMatrix(glm::mat4 model){
        m_modelMatrix = model;
    }
    
    
protected:
    glm::mat4 m_modelMatrix = glm::mat4(1.0f);
    glm::vec3 m_position = glm::vec3(1.0f);
    glm::vec3 m_scale = glm::vec3(1.0f);
    glm::vec3 m_rotation = glm::vec3(1.0f);
    DrawMode m_drawMode = DrawMode::DEFAULT;

    
};

#endif /* MeshBase_h */
