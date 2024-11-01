//
//  Mesh.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 01/09/2024.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "./Vertex.h"

#include "../Material/Shader.hpp"
#include "../Material/Texture.hpp"
#include "../Material/MaterialBase.hpp"
#include "../Material/SolidMaterial.hpp"

#include "./MeshBase.h"

#include "../Scene/Camera.hpp"

#include "../Backend/VBO.hpp"
#include "../Backend/VAO.hpp"
#include "../Backend/EBO.hpp"

#include "../Utility/Color.h"
#include "../Utility/Transform.hpp"



class Mesh : public MeshBase{
    
public:
    
    Mesh(std::vector<Vertex> vertices,
         std::vector<GLuint> elements,
         std::vector<Texture> textures);
    
    ~Mesh(){
        //delete m_wireMaterial;
    };
    
    void onDraw(Camera& camera) override;
    void onInput(SDL_Event& event) override;
    
    void setMaterial(const MaterialBase& material) override;
    void setDrawMode(DrawMode mode) override;
    
    void setPosition(float x, float y, float z) override;
    void setScale(float x, float y, float z) override;
    void setRotation(float degree, float x, float y, float z) override;
    void lookAt(float x, float y, float z) override;
    
    std::vector<Vertex>& getVertices(){ return m_vertices; };
    std::vector<GLuint>& getIndices(){ return m_elements; };
    std::vector<Texture>& getTextures(){ return m_textures; };
    
    void addTexture(Texture& texture){
        m_textures.push_back(texture);
    }
    
    MaterialBase* getMaterial(){
        return material;
    }

private:
    
    SolidMaterial* m_wireMaterial = nullptr;
    void setWireMaterial(glm::vec3 color = Color::Green);
    
    MaterialBase* material = nullptr;
    
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_elements;
    std::vector<Texture> m_textures;
    
    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
    
    GLenum m_usage;
    
};

#endif /* Mesh_hpp */
