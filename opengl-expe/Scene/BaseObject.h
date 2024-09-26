//
//  BaseObject.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 26/09/2024.
//

#ifndef BaseObject_h
#define BaseObject_h


class BaseObject{
    
public:
    
    enum class Type{
        CAMERA,
        OBJECT,
        LIGHT
    };
    
    BaseObject(Type t) : type(t){}
    virtual ~BaseObject(){}; //make class "polymorphic", for dynamic casting
    
    Type type;

};

#endif /* BaseObject_h */
