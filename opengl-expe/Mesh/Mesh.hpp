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

#include "../Scene/GameObject.hpp"

#include "./Vertex.h"
#include "../Material/Shader.hpp"
#include "../Material/Texture.hpp"
#include "../Utility/Transform.hpp"
#include "../Material/Material.hpp"

#include "../Scene/Camera.hpp"
#include "../Backend/VBO.hpp"
#include "../Backend/VAO.hpp"
#include "../Backend/EBO.hpp"

class Mesh : public GameObject{
    
public:
    
    Mesh(std::vector<Vertex> vertices,
         std::vector<GLuint> elements,
         std::vector<Texture> textures);
    
    ~Mesh();
    
    void draw(Camera& camera) override;
    void setMaterial(Material& material) override;
    
    std::vector<GLuint> getIndices();

private:
    
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_elements;
    std::vector<Texture> m_textures;
    
    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
    
    Material* material;
    
    GLenum m_usage;
    
};

#endif /* Mesh_hpp */
