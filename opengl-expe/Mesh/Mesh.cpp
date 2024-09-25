//
//  Mesh.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 01/09/2024.
//


#include <iostream>

#include "Mesh.hpp"
#include "../Utility/Utility.hpp"


Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& elements, std::vector<Texture>& textures):
m_vertices(vertices),
m_elements(elements),
m_textures(textures){
    //Instantiate our buffers and array object and load data in it
    //We then proceed to layout the VAO data only when loading the Shader
    
    //Vertex Array Object (define how to interpret vbo data)
    m_vao.bind();
    
    //Vertex buffer Array (simply buffer the vertex data))
    m_vbo.setData(m_vertices);
    
    //Elements array
    m_ebo.setData(m_elements);
    
    m_vao.unbind();
    
};

Mesh::~Mesh(){
    delete shader;
    delete texture;
}

void Mesh::loadShader(const std::string& vertShader, const std::string& fragShader, const std::string& fragName){
    
    const char* cVertShader = vertShader.c_str();
    const char* cFragShader = fragShader.c_str();
    const char* cFragName = fragName.c_str();
    
    shader = new Shader(cVertShader, cFragShader, cFragName);

    shader->loadProgram();
    
    //map out the VAO data into our shader
    shader->use();
    /*
     By default we will the the following location order:
     0: position    (vec3)
     1: normal      (vec3)
     2: color       (vec3)
     3: uv          (vec2)
     our reference point is the Vertex structure
     */
    shader->setAttribute("position", (int) m_vertices.size(), 3, nullptr);
    shader->setAttribute("normal", (int) m_vertices.size(), 3, (void*)( 3 * m_vertices.size()));
    shader->setAttribute("color", (int) m_vertices.size(), 3, (void*)( 6 * m_vertices.size()));
    shader->setAttribute("uv", (int) m_vertices.size(), 2, (void*)( 9 * m_vertices.size()));
    
    
}

void Mesh::loadTexture(std::string& path, unsigned int slot){
    
    texture = new Texture(path, slot);
    texture->load();
    
}


