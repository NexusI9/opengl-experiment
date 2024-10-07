//
//  Material.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 02/10/2024.
//

#include "BasicMaterial.hpp"


void BasicMaterial::loadShader(const std::string &vertShader, const std::string &fragShader, const std::string &fragName) {

    const char* cVertShader = vertShader.c_str();
    const char* cFragShader = fragShader.c_str();
    const char* cFragName = fragName.c_str();
    
    m_shader = new Shader(cVertShader, cFragShader, cFragName);
    
    //map out the VAO data into our shader
    
    /*
     By default we will the the following location order:
     0: position    (vec3)
     1: normal      (vec3)
     2: color       (vec3)
     3: uv          (vec2)
     our reference point is the Vertex structure
     */
    
    m_shader->setAttribute(m_vao, m_vbo, "position", 3, sizeof(Vertex), (void*) 0);
    m_shader->setAttribute(m_vao, m_vbo, "normal", 3, sizeof(Vertex), (void*)( 3 * sizeof(float)));
    m_shader->setAttribute(m_vao, m_vbo, "color", 3, sizeof(Vertex), (void*)( 6 *  sizeof(float)));
    m_shader->setAttribute(m_vao, m_vbo, "uv", 2, sizeof(Vertex), (void*)( 9 * sizeof(float)));
    m_shader->use();
}
