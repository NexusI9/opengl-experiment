//
//  Loader.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 05/10/2024.
//

#ifndef Loader_h
#define Loader_h

#include <stdio.h>
#include <vector>
#include "../Mesh/Mesh.hpp"
#include "../Mesh/MeshGroup.hpp"

class Loader{
  
public:
    
    Loader(){};
    virtual ~Loader(){};
    MeshGroup* getMesh(){
        return m_meshGroup;
    };
    
protected:
    
    MeshGroup* m_meshGroup;
    std::vector<Mesh*> m_meshes;
    
};

#endif /* Loader_hpp */
