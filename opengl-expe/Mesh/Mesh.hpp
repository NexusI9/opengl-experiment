//
//  Mesh.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 01/09/2024.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "./Vertex.h"

#include "../Material/Shader.hpp"
#include "../Material/Texture.hpp"
#include "../Material/MaterialBase.hpp"
#include "../Material/SolidMaterial.hpp"

#include "./MeshBase.h"

#include "../Scene/Camera.hpp"

#include "../Backend/VBO.hpp"
#include "../Backend/VAO.hpp"
#include "../Backend/EBO.hpp"

#include "../Utility/Color.h"
#include "../Utility/Transform.hpp"



struct MeshArgsBuffer{
    std::string name = "DEFAULT";
    VBO vbo;
    VAO vao;
    EBO ebo;
    std::vector<Texture> textures;
};

struct MeshArgsVertex{
    std::string name = "DEFAULT";
    std::vector<Vertex> vertices;
    std::vector<VertexElement> elements;
    std::vector<Texture> textures;
};

class Mesh : public MeshBase{
    
public:
    
    /**
     Can Instantiate mesh with 2 different approach:
     1. Vertex Based: Passing arrays of vertex and elements, from which the Mesh will automatically generate the VAO, VBO and EBO from those data
     2. Buffer Based: Passing direclty some presetup buffers that will directly be assigned to the material
     */
    Mesh(const MeshArgsVertex& args);
    Mesh(const MeshArgsBuffer& args);
    
    ~Mesh(){
        //delete m_wireMaterial;
    };
    
    void onDraw(Camera& camera) override;
    void onInput(SDL_Event& event) override;
    
    void setMaterial(const MaterialBase& material) override;
    void setDrawMode(DrawMode mode) override;
    
    void setPosition(float x, float y, float z) override;
    void setScale(float x, float y, float z) override;
    void setScale(float value) override;
    void setRotation(float degree, float x, float y, float z) override;
    void lookAt(float x, float y, float z) override;
    
    std::string getName(){ return m_name; }
    std::vector<Vertex>& getVertices(){ return m_vertices; };
    std::vector<GLuint>& getIndices(){ return m_elements; };
    std::vector<Texture>& getTextures(){ return m_textures; };
    
    void addTexture(Texture& texture){
        m_textures.push_back(texture);
    }
    
    MaterialBase* getMaterial(){
        return material;
    }

private:
    
    SolidMaterial* m_wireMaterial = nullptr;
    void setWireMaterial(glm::vec3 color = Color::Green);
    
    MaterialBase* material = nullptr;
    
    std::string m_name;
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_elements;
    std::vector<Texture> m_textures;
    
    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
    
    GLenum m_usage;
    
};

#endif /* Mesh_hpp */
