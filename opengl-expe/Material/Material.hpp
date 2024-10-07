//
//  Material.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 04/10/2024.
//

#ifndef Material_hpp
#define Material_hpp

#include <stdio.h>
#include <string>
#include "./Shader.hpp"
#include "../Mesh/Vertex.h"
#include "../Backend/VBO.hpp"
#include "../Backend/VAO.hpp"

/*
 A "Material" Object acts as a shader preset. Meaning that the directory may hold a Bunch of premade materials (BasicMaterial, CustomMaterial).
 This approach allows to narrow and own more control over the shader creation. Instead of loading Shader files by shader files, we now may just need to invoke a material that will own some preloaded shader along with the vertex attribute pointer automatically link.
 The idea is to only pass the vertex and other attributes, and the material will automatically plug those attributes to the vertex and fragment shader. Such approach throttle freedom but will save some time on the long run.
 Of course the "CustomMaterial" above may provide more flexibility.
 */

class Material{
    
public:
    
    Material(VAO& vao, VBO& vbo, std::vector<Vertex>& vertices): m_vao(vao), m_vbo(vbo), m_vertices(vertices){
    };
    
    ~Material(){
        delete m_shader;
    };
    
protected:
    
    VAO& m_vao;
    VBO& m_vbo;
    Shader* m_shader;
    
    std::vector<Vertex>& m_vertices;
    
    virtual void loadShader(const std::string& vertShader, const std::string& fragShader, const std::string& fragName) = 0;
    
};

#endif /* Material_hpp */
