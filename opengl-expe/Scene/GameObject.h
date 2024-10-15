//
//  BaseObject.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 26/09/2024.
//

#ifndef GameObject_h
#define GameObject_h

#include "./Camera.hpp"

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
    Type type;

};

#endif /* BaseObject_h */
