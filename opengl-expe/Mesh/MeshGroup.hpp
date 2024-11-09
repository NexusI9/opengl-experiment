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
    
    MeshGroup(std::vector<Mesh> meshes = {}): m_meshes(meshes){};
    ~MeshGroup(){};
    
    std::vector<Mesh>& getMeshes(){ return m_meshes; }
    
    void onDraw(Camera& camera) override;
    void onInput(SDL_Event& event) override;
    
    void setMaterial(const MaterialBase& material) override;
    void setDrawMode(DrawMode mode) override;
    
    void setPosition(float x, float y, float z) override;
    void setScale(float x, float y, float z) override;
    void setScale(float value) override;
    void setRotation(float degree, float x, float y, float z) override;
    void lookAt(float x, float y, float z) override;
    
    void addChild(Mesh&& mesh){
        m_meshes.push_back(std::move(mesh));
    }
    
    void addChildren(MeshGroup* source){
        for(Mesh& child : source->m_meshes) addChild(std::move(child));
    }
    
    void addChildren(std::vector<Mesh>& source){
        for(Mesh& child : source) addChild(std::move(child));
    }
    
    void addTexture(Texture& texture){
        for(auto& mesh : m_meshes) mesh.addTexture(texture);
    }
    
    int size(){
        return (int) m_meshes.size();
    }
    
private:
    
    std::vector<Mesh> m_meshes;
    
};

#endif /* MeshGroup_hpp */
