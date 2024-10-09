//
//  Loader.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 05/10/2024.
//

#ifndef Model_h
#define Model_h

#include <stdio.h>
#include <vector>
#include "../Mesh/Mesh.hpp"
#include "../Mesh/MeshGroup.hpp"

class Model{
  
public:
    
    Model(){};
    virtual ~Model(){};
    MeshGroup* getMesh(){
        return m_meshGroup;
    };
    
protected:
    
    MeshGroup* m_meshGroup;
    std::vector<Mesh*> m_meshes;
    
};

#endif /* Loader_hpp */
