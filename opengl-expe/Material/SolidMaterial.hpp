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
/*
 Solid Material take a simple Color (vector 3) as parameter
 */
class SolidMaterial : public MaterialBase{
    
public:
    SolidMaterial(glm::vec3 clr = Color::Green,
                  std::string vertPath = std::string(ROOT_DIR + "Material/Shader/solid.vert"),
                  std::string fragPath = std::string(ROOT_DIR + "Material/Shader/solid.frag"))
    : color(clr), m_vertexPath(vertPath), m_fragmentPath(fragPath){}

    void setColor(glm::vec3 cl){
        if(m_shader == nullptr){ return; }
        color = cl;
        m_shader->use();
        m_shader->setVec3("color", color);
    }
 
protected:
    
    void loadShader() override {
        
        const std::string cVertShader = std::string(m_vertexPath);
        const std::string cFragShader = std::string(m_fragmentPath);
        const std::string cFragName = "outColor";
        
        m_shader = new Shader(cVertShader.c_str(), cFragShader.c_str(), cFragName.c_str());
        
        //map out the VAO data into our shader
        m_shader->setAttribute(*m_vao, *m_vbo, "position", 3, sizeof(Vertex), (void*) 0);
        m_shader->setAttribute(*m_vao, *m_vbo, "uv", 2, sizeof(Vertex), (void*)( 9 * sizeof(float)));
        m_shader->use();
        
        //Set material color
        setColor(color);
    };
    
private:
    
    glm::vec3 color = Color::Green;
    const std::string m_fragmentPath;
    const std::string m_vertexPath;

};

#endif /* SolidMaterial_h */
