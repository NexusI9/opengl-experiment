//
//  SolidMaterial.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 12/10/2024.
//

#ifndef SolidMaterial_hpp
#define SolidMaterial_hpp

#include <unordered_map>

#include "./MaterialBase.hpp"
#include "../Utility/Constant.h"
#include "../Utility/Color.h"
#include "./Uniform.h"

struct SolidMaterialArg{
    glm::vec3 color = Color::Green;
    std::string vertexShader = std::string(ROOT_DIR + "Material/Shader/solid.vert");
    std::string fragmentShader = std::string(ROOT_DIR + "Material/Shader/solid.frag");
    UniformList uniforms;
};

/*
 Solid Material take a simple Color (vector 3) as parameter
 */
class SolidMaterial : public MaterialBase{
    
public:

    SolidMaterial(const SolidMaterialArg& args) : color(args.color), m_vertexPath(args.vertexShader), m_fragmentPath(args.fragmentShader), m_uniforms(args.uniforms){}

    void setColor(glm::vec3 cl){
        if(m_shader == nullptr){ return; }
        color = cl;
        m_shader->use();
        m_shader->setVec3("color", color);
    }
    
    SolidMaterial* clone() const override{
        return new SolidMaterial(*this);
    }

 
protected:
    
    void loadShader() override {

        const std::string cFragName = "outColor";
        
        m_shader = new Shader(m_vertexPath, m_fragmentPath, cFragName);
        
        //map out the VAO data into our shader
        m_shader->setAttribute(*m_vao, *m_vbo, "position", 3, sizeof(Vertex), (void*) 0);
        m_shader->setAttribute(*m_vao, *m_vbo, "uv", 2, sizeof(Vertex), (void*)( 9 * sizeof(float)));
        m_shader->use();
        
        //Assign uniforms
        assignUniforms(m_uniforms);
        
        //Set material color
        setColor(color);
    };
    
private:
    
    glm::vec3 color = Color::Green;
    const std::string m_fragmentPath;
    const std::string m_vertexPath;
    UniformList m_uniforms;

};

#endif /* SolidMaterial_h */
