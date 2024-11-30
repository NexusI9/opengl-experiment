//
//  SolidMaterial.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 12/10/2024.
//

#ifndef CustomMaterial_hpp
#define CustomMaterial_hpp

#include <unordered_map>

#include "./MaterialBase.hpp"
#include "../Utility/Constant.h"
#include "../Utility/Color.h"
#include "./Uniform.h"

struct CustomMaterialArg{
    std::string vertexShader = std::string(ROOT_DIR + "Material/Shader/default.vert");
    std::string fragmentShader = std::string(ROOT_DIR + "Material/Shader/default.frag");
    UniformList uniforms;
};

/*
Custom Material, for more flexible and customizable
 */
class CustomMaterial : public MaterialBase{
    
public:

    CustomMaterial(const CustomMaterialArg& args): m_vertexPath(args.vertexShader), m_fragmentPath(args.fragmentShader), m_uniforms(args.uniforms){}
    
    CustomMaterial* clone() const override{
        return new CustomMaterial(*this);
    }

 
protected:
    
    void loadShader() override {

        const std::string cFragName = "outColor";
        
        m_shader = new Shader(m_vertexPath, m_fragmentPath, cFragName);
        
        //Assign uniforms
        assignUniforms(m_uniforms);
        
    };
    
private:
    
    const std::string m_fragmentPath;
    const std::string m_vertexPath;
    UniformList m_uniforms;

};

#endif /* SolidMaterial_h */
