//
//  MeshBase.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 09/10/2024.
//

#ifndef MeshBase_h
#define MeshBase_h

#include "../Scene/GameObject.h"
#include"../Material/MaterialBase.hpp"
#include <glm/glm.hpp>

class MeshBase : public GameObject{
    
public:
    
    MeshBase() : GameObject(Type::OBJECT){};
    
    enum class DrawMode{
        DEFAULT,
        WIREFRAME,
        DEBUGGER
    };
    
    virtual void setMaterial(MaterialBase& material) = 0;
    virtual void setDrawMode(DrawMode mode) = 0;
    
    virtual void setPosition(float x, float y, float z) = 0;
    virtual void setScale(float x, float y, float z) = 0;
    virtual void setRotation(float degree, float x, float y, float z) = 0;
    
    glm::mat4 getModelMatrix(){
        return m_modelMatrix;
    }
    
    void setModelMatrix(glm::mat4 model){
        m_modelMatrix = model;
    }
    
    
protected:
    glm::mat4 m_modelMatrix = glm::mat4(1.0f);

    
};

#endif /* MeshBase_h */
