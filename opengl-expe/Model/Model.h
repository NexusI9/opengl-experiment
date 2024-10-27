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
    virtual ~Model(){
        //dispose inner Mesh
        for(auto& mesh : m_meshGroup->getMeshes()) delete mesh;
        //dispose global meshgroup
        delete m_meshGroup;
    };
    
    MeshGroup* getMesh(){
        return m_meshGroup;
    };
    
    MeshGroup* copy(){
        std::vector<Mesh*> innerMeshCopy;
        for(auto& mesh : m_meshes) innerMeshCopy.push_back(new Mesh(*mesh));
        return new MeshGroup(innerMeshCopy);
    };
    
    
protected:
    
    MeshGroup* m_meshGroup;
    
    //"root" so no use reference vector to keep original generated Mesh in memory
    std::vector<Mesh*> m_meshes;
    
};

#endif /* Loader_hpp */
