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
#include <vector>

#include "Vertex.h"
#include "Shader.hpp"
#include "Texture.hpp"
#include "../Utility/Transform.hpp"
#include "../Scene/Camera.hpp"
#include "../Backend/VBO.hpp"
#include "../Backend/VAO.hpp"
#include "../Backend/EBO.hpp"

class Mesh{
    
public:
    
    Mesh(std::vector<Vertex>& vertices,
         std::vector<GLuint>& elements,
         std::vector<Texture>& textures);
    ~Mesh();
    
    void loadShader(const std::string& vertShader, const std::string& fragShader, const std::string& fragName);
    
    void loadTexture(std::string& path, unsigned int slot);
    
    void draw(Camera& camera, glm::mat4 matrix, Transform& tranform);
    
    Shader* shader = nullptr;
    Texture* texture = nullptr;
    

private:
    
    std::vector<Vertex>& m_vertices;
    std::vector<GLuint>& m_elements;
    std::vector<Texture>& m_textures;
    
    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
    
    GLenum m_usage;
    
};

#endif /* Mesh_hpp */
