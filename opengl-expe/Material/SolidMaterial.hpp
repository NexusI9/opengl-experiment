//
//  SolidMaterial.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 12/10/2024.
//

#ifndef SolidMaterial_hpp
#define SolidMaterial_hpp

#include "./MaterialBase.hpp"
#include "../Utility/Constant.h"
#include "../Utility/Color.h"

class SolidMaterial : public MaterialBase{
    
public:
    SolidMaterial(){}

    
    void setColor(glm::vec3 cl){
        if(m_shader == nullptr){ return; }
        color = cl;
        m_shader->use();
        m_shader->setVec3("color", color);
    }
 
protected:
    
    void loadShader() override {
        
        const std::string cVertShader = std::string(ROOT_DIR + "Material/Shader/solid.vert");
        const std::string cFragShader = std::string(ROOT_DIR + "Material/Shader/solid.frag");
        const std::string cFragName = "outColor";
        
        m_shader = new Shader(cVertShader.c_str(), cFragShader.c_str(), cFragName.c_str());
        
        //map out the VAO data into our shader
        m_shader->setAttribute(*m_vao, *m_vbo, "position", 3, sizeof(Vertex), (void*) 0);
        m_shader->use();
    };
    
private:
    
    glm::vec3 color = Color::Green;

};

#endif /* SolidMaterial_h */
