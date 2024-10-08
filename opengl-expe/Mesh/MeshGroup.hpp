//
//  MeshGroup.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 07/10/2024.
//

#ifndef MeshGroup_hpp
#define MeshGroup_hpp

#include <stdio.h>
#include <vector>

#include "./Mesh.hpp"
#include "../Scene/GameObject.hpp"
#include "../Scene/Camera.hpp"

class MeshGroup : public GameObject{
    
public:
    
    MeshGroup(std::vector<Mesh*> meshes):GameObject(Type::OBJECT), m_meshes(meshes){};
    ~MeshGroup(){
        for(Mesh* mesh : m_meshes) delete mesh;
    };
    
    std::vector<Mesh*> getMeshes(){ return m_meshes; }
    
    void draw(Camera& camera) override;
    void setMaterial(Material& material) override;
    
private:
    
    std::vector<Mesh*> m_meshes;
    
};

#endif /* MeshGroup_hpp */
