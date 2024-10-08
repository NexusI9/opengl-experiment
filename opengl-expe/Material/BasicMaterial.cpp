//
//  Material.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 02/10/2024.
//

#include "BasicMaterial.hpp"
#include "../Utility/Constant.h"


void BasicMaterial::loadShader() {

    const std::string cVertShader = std::string(ROOT_DIR + "Material/Shader/default.vert");
    const std::string cFragShader = std::string(ROOT_DIR + "Material/Shader/default.frag");
    const std::string cFragName = "outColor";
    
    m_shader = new Shader(cVertShader.c_str(), cFragShader.c_str(), cFragName.c_str());
    
    //map out the VAO data into our shader
    
    /*
     By default we will the the following location order:
     0: position    (vec3)
     1: normal      (vec3)
     2: color       (vec3)
     3: uv          (vec2)
     our reference point is the Vertex structure
     */

    m_shader->setAttribute(*m_vao, *m_vbo, "position", 3, sizeof(Vertex), (void*) 0);
    m_shader->setAttribute(*m_vao, *m_vbo, "normal", 3, sizeof(Vertex), (void*)( 3 * sizeof(float)));
    m_shader->setAttribute(*m_vao, *m_vbo, "color", 3, sizeof(Vertex), (void*)( 6 *  sizeof(float)));
    m_shader->setAttribute(*m_vao, *m_vbo, "uv", 2, sizeof(Vertex), (void*)( 9 * sizeof(float)));
    m_shader->use();
}
