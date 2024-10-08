//
//  BaseObject.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 26/09/2024.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "./Camera.hpp"
#include "../Material/Material.hpp"

class GameObject{
    
public:
    
    enum class Type{
        OBJECT,
        LIGHT,
        MATERIAL
    };
    
    GameObject(Type t) : type(t){}
    virtual ~GameObject(){} //make class "polymorphic", for dynamic casting
    
    virtual void draw(Camera& camera) = 0;
    virtual void setMaterial(Material& material) = 0;
    Type type;

};

#endif /* BaseObject_h */
