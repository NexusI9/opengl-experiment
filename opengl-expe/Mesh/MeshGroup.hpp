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

#include "./MeshBase.h"
#include "./Mesh.hpp"
#include "../Scene/Camera.hpp"

class MeshGroup : public MeshBase{
    
public:
    
    MeshGroup(std::vector<Mesh*>& meshes): m_meshes(meshes){};
    ~MeshGroup(){};
    
    std::vector<Mesh*>& getMeshes(){ return m_meshes; }
    
    void draw(Camera& camera) override;
    void setMaterial(MaterialBase& material) override;
    void setDrawMode(DrawMode mode) override;
    
    void setPosition(float x, float y, float z) override;
    void setScale(float x, float y, float z) override;
    void setRotation(float degree, float x, float y, float z) override;
    void lookAt(float x, float y, float z) override;
    
    void addChild(Mesh* mesh){
        m_meshes.push_back(mesh);
    }
    
    void transferChildren(MeshGroup* target){
        for(Mesh* child : m_meshes) target->addChild(child);
    }
    
    int size(){
        return (int) m_meshes.size();
    }
    
private:
    
    std::vector<Mesh*>& m_meshes;
    
};

#endif /* MeshGroup_hpp */
