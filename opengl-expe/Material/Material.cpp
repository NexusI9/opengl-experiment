//
//  Material.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 04/10/2024.
//

#include "Material.hpp"
#include "../Utility/Debugger.hpp"


void Material::draw(Camera& camera){
    
    if(m_shader == nullptr){
        Debugger::print("No shader were found, mesh won't be rendered.", Verbose::Flag::MESH);
        return;
    }

    m_shader->use();
    m_shader->setUniformBlock("Camera", camera.getMatrixBindingIndex());
    m_shader->setMatrix4("model", glm::mat4(1.0f));
    
    //Apply texture to shader
    if(m_textures != nullptr){
        for(int t = 0; t < m_textures->size(); t++){
            (*m_textures)[t].bind();
            m_shader->setSampler2D("texture"+std::to_string(t), t);
        }
    }

    
}
