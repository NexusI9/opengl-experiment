//
//  Loader.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 05/10/2024.
//

#include "Loader.hpp"
#include "./Mesh.hpp"


class Loader{
    
public:
    
    Loader();
    virtual ~Loader();
    
    virtual Mesh* getMesh();
    
};
