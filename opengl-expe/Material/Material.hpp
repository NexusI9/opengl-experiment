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
#include <glm/glm.hpp>
#include "./Texture.hpp"
#include "./Shader.hpp"
#include "../Mesh/Vertex.h"
#include "../Backend/VBO.hpp"
#include "../Backend/VAO.hpp"
#include "../Scene/Camera.hpp"

/*
 A "Material" Object acts as a shader preset. Meaning that the directory may hold a Bunch of premade materials (BasicMaterial, CustomMaterial).
 This approach allows to narrow and own more control over the shader creation. Instead of loading Shader files by shader files, we now may just need to invoke a material that will own some preloaded shader along with the vertex attribute pointer automatically link.
 The idea is to only pass the vertex and other attributes, and the material will automatically plug those attributes to the vertex and fragment shader. Such approach throttle freedom but will save some time on the long run.
 Of course the "CustomMaterial" above may provide more flexibility.
 */

class Material{
    
public:
    
    Material(){};
    ~Material(){
        delete m_shader;
    };
    
    void init(VAO& vao, VBO& vbo, std::vector<Vertex>& vertices, std::vector<Texture>& textures){
        m_vao = &vao;
        m_vbo = &vbo;
        m_vertices = &vertices;
        m_textures = &textures;
        
        loadShader();
    }
    
    
    void draw(Camera& camera, glm::mat4 modelMatrix = glm::mat4(1.0f));
    
protected:
    
    VAO* m_vao = nullptr;
    VBO* m_vbo = nullptr;
    Shader* m_shader = nullptr;
    std::vector<Vertex>* m_vertices = nullptr;
    std::vector<Texture>* m_textures = nullptr;
    
    virtual void loadShader() = 0;
    
};

#endif /* Material_hpp */
