//
//  MeshBase.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 09/10/2024.
//

#ifndef MeshBase_h
#define MeshBase_h

#include "../Scene/GameObject.h"
#include"../Material/Material.hpp"

class MeshBase : public GameObject{
    
public:
    
    MeshBase() : GameObject(Type::OBJECT){};
    
    enum class DrawMode{
        DEFAULT,
        WIREFRAME,
        DEBUGGER
    };
    
    virtual void setMaterial(Material& material) = 0;
    virtual void setDrawMode(DrawMode mode) = 0;
    
};

#endif /* MeshBase_h */
