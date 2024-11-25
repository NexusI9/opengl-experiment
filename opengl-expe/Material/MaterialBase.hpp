//
//  Material.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 04/10/2024.
//

#ifndef MaterialBase_hpp
#define MaterialBase_hpp

#include <stdio.h>
#include <string>
#include <glm/glm.hpp>
#include <unordered_map>

#include "./Texture.hpp"
#include "./Shader.hpp"
#include "../Mesh/Vertex.h"
#include "../Backend/VBO.hpp"
#include "../Backend/VAO.hpp"
#include "../Scene/Camera.hpp"
#include "./Uniform.h"

/*
 A "Material" Object acts as a shader preset. Meaning that the directory may hold a Bunch of premade materials (BasicMaterial, CustomMaterial).
 
 This approach allows to narrow and own more control over the shader creation. Instead of loading Shader files by shader files, we now may just need to invoke a material that will own some preloaded shader along with the vertex attribute pointer automatically link.
 
 The idea is to only pass the VAO and other attributes, and the material will automatically map those attributes to the vertex and fragment shader. Such approach throttle freedom but will save some time on the long run.
 
 Another benefit of using Material is its draw method that will automatically update the universal View and Projection matrix based on camera position
 
 Of course the "CustomMaterial" above may provide more flexibility.
 */


class MaterialBase{
    
public:
    
    MaterialBase() = default;
    ~MaterialBase(){
        delete m_shader;
    };
    
    void init(VAO& vao, VBO& vbo, std::vector<Texture>& textures){
        /**
         Initialize the material afterward since the process operate as the following:
         1. Create Mesh
         2. Create Material
         3. Plug Material -> to Mesh
         4. Material init with Mesh VAO, VBO and textures
         
         Since we don't have access to the private mesh VAO and VBO, we can't plug it during the initialization.
         Also the Idea is to first configurate the material, before pluging it to the Mesh afterward.
         This approach also ensure the material stays malleable and can be assigned to multiple mesh (i.e. vao) during runtime.
         */
        
        m_vao = &vao;
        m_vbo = &vbo;
        m_textures = &textures;
        loadShader();
    }
    
    void init(Shader& shader){
        /**
         Second approach of initializing the material is to directly pass a shader that has already a VAO correctly linked in.
         This is useful when we use a shader that doesn't follow the casual vertex pipeline and requires additional location assignments.
         */
        delete m_shader;
        m_shader = new Shader(shader);
    }
    
    void onDraw(Camera& camera, glm::mat4 modelMatrix = glm::mat4(1.0f));
    
    Shader* getShader(){ return m_shader; }
    virtual MaterialBase* clone() const = 0;
    
protected:
    
    VAO* m_vao = nullptr;
    VBO* m_vbo = nullptr;
    Shader* m_shader = nullptr;
    std::vector<Texture>* m_textures = nullptr;
    
    void assignUniforms(UniformList uniforms);
    
    virtual void loadShader() = 0;
        

    
};

#endif /* Material_hpp */
