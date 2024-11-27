//
//  Prefab.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 24/11/2024.
//

#ifndef Prefab_h
#define Prefab_h

#include "../Mesh/Mesh.hpp"

/**
 A prefab inherit from the initial Model class but include an automatic Material managmenent system.
 Model are only aime to be pure vertex and elements vector, whereas prefab are "ready-made" assets made to be quickly used.
 */
class Prefab{
    
public:
    
    Prefab() = default;
    ~Prefab(){};
    
    Mesh* getMesh(){
        return m_mesh;
    };
    
protected:
    
    Mesh* m_mesh;

};

#endif /* Prefab_h */
