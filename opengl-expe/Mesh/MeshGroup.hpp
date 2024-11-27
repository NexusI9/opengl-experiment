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
#include <SDL2/SDL.h>

#include "./MeshBase.h"
#include "./Mesh.hpp"
#include "../Scene/Camera.hpp"

class MeshGroup : public MeshBase{
    
public:
    
    MeshGroup() = default;
    ~MeshGroup(){};
    
    void onDraw(Camera& camera) override;
    void onInput(SDL_Event& event) override;
    
    void setMaterial(const MaterialBase& material) override;
    void setDrawMode(DrawMode mode) override;
    
    void setPosition(float x, float y, float z) override;
    void setScale(float x, float y, float z) override;
    void setScale(float value) override;
    void setRotation(float degree, float x, float y, float z) override;
    void lookAt(float x, float y, float z) override;
    
    void addChild(MeshBase* mesh) override{
        m_children.push_back(mesh);
    }
    
    void addChildren(MeshBase* source) override{
        for(auto& child : source->getChildren()) addChild(child);
    }
    
    void addChildren(std::vector<MeshBase*>& source) override{
        for(auto& child : source) addChild(child);
    }
    
    void addTexture(Texture& texture) override{
        for(auto& mesh : m_children) mesh->addTexture(texture);
    }
    
    int size(){
        return (int) m_children.size();
    }
    

    
};

#endif /* MeshGroup_hpp */
