//
//  BaseObject.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 26/09/2024.
//

#ifndef GameObject_h
#define GameObject_h

#include <SDL2/SDL.h>
#include "./Camera.hpp"

//Abstract GameObject class
class GameObject{
    
public:
    
    enum class Type{
        OBJECT,
        LIGHT,
        MATERIAL,
    };

    int ID;
    GameObject(Type t) : type(t){}
    
    virtual ~GameObject(){} //make class "polymorphic", for dynamic casting
    
    virtual void onDraw(Camera& camera) = 0;
    virtual void onInput(SDL_Event& event) = 0;
    
    Type type;

};

#endif /* BaseObject_h */
