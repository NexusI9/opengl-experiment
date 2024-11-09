//
//  Material.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 04/10/2024.
//

#include "MaterialBase.hpp"
#include "../Utility/Debugger.hpp"


void MaterialBase::onDraw(Camera& camera, glm::mat4 modelMatrix){
    
    if(m_shader == nullptr){
        Debugger::print("No shader were found, mesh won't be rendered.", Verbose::Flag::MESH);
        return;
    }

    m_shader->use();
    m_shader->setUniformBlock("Camera", camera.getMatrixBindingIndex());
    m_shader->setMatrix4("model", modelMatrix);
    
    //Apply texture to shader
    for(int t = 0; t < m_textures.size(); t++){
            m_textures[t].bind();
            m_shader->setSampler2D("texture"+std::to_string(t), t);
    }
    
}


void MaterialBase::assignUniforms(UniformList uniforms){
    
    if(!m_shader){
        std::cout << "ERROR :: MaterialBase :: Cannot assign uniforms, no shader existing" << std::endl;
        return;
    }
    
    for(auto& uniform : uniforms){
        
        switch(uniform.type){
                
            case UniformType::FLOAT:
                if(auto value = std::get_if<float>(&uniform.value) )
                    m_shader->setFloat(uniform.name, *value);
                break;
                
            case UniformType::INT:
                if(auto value = std::get_if<int>(&uniform.value) )
                    m_shader->setInt(uniform.name, *value);
                break;
                
            case UniformType::VECTOR_2:
                if(auto value = std::get_if<glm::vec2>(&uniform.value) )
                    m_shader->setVec2(uniform.name, *value);
                break;
                
            case UniformType::VECTOR_3:
                if(auto value = std::get_if<glm::vec3>(&uniform.value) )
                m_shader->setVec3(uniform.name, *value);
                break;
                
            case UniformType::SAMPLER_2D:
                if(auto value = std::get_if<int>(&uniform.value) )
                    m_shader->setSampler2D(uniform.name, *value);
                break;
                
            case UniformType::MATRIX_4:
                if(auto value = std::get_if<glm::mat4>(&uniform.value) )
                    m_shader->setMatrix4(uniform.name, *value);
                break;
                
            case UniformType::BOOLEAN:
                if(auto value = std::get_if<bool>(&uniform.value) )
                    m_shader->setBoolean(uniform.name, *value);
                break;
                
            case UniformType::UNIFORM_BLOCK:
                if(auto value = std::get_if<GLuint>(&uniform.value) )
                    m_shader->setUniformBlock(uniform.name, *value);
                break;
                
        }
        
    }
}
