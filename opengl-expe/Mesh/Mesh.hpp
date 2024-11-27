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

#include "../Scene/GameObject.h"

#include "../Scene/Camera.hpp"

#include "../Backend/VBO.hpp"
#include "../Backend/VAO.hpp"
#include "../Backend/EBO.hpp"

#include "../Utility/Color.h"
#include "../Utility/Transform.hpp"

#include "../Model/Model.h"



struct MeshArgsBuffer{
    std::vector<Texture> textures;
    std::string          name = "DEFAULT";
    VBO vbo;
    VAO vao;
    EBO ebo;
};

struct MeshArgsVertex{
    std::string                 name = "DEFAULT";
    std::vector<Vertex>         vertices;
    std::vector<VertexElement>  elements;
    std::vector<Texture>        textures;
};

struct MeshArgsModel{
    std::string name = "DEFAULT";
    Model&      model;
};

class Mesh : public GameObject{
    
public:
    
    /**
     Can Instantiate mesh with 2 different approach:
     1. Vertex Based: Passing arrays of vertex and elements, from which the Mesh will automatically generate the VAO, VBO and EBO from those data and then only pass it to the material. (middle man)
     2. Buffer Based: Passing direclty some pre-set buffers that will directly be assigned to the material. (no middle man, full vbo/vao control)
     3. Model Based: Passing a Model (which include a preset of vertex and elements)
     */

    Mesh() : GameObject(Type::OBJECT){};
    Mesh(const MeshArgsVertex& args);
    Mesh(const MeshArgsBuffer& args);
    Mesh(const MeshArgsModel& args);
    
    enum class DrawMode{
        DEFAULT,
        WIREFRAME,
        DEBUGGER,
        POINTS
    };
    
    ~Mesh(){
        //delete m_wireMaterial;
    };
    
    void onDraw(Camera& camera) override;
    void onInput(SDL_Event& event) override;
    
    void setMaterial(const MaterialBase& material);
    void setDrawMode(DrawMode mode);
    
    void setPosition(float x, float y, float z);
    void setScale(float x, float y, float z);
    void setScale(float value);
    void setRotation(float degree, float x, float y, float z);
    void lookAt(float x, float y, float z);
    
    glm::vec3 getPosition(){
        return m_position;
    }
    
    glm::vec3  getScale(){
        return m_scale;
    }
    
    glm::vec3  getRotation(){
        return m_rotation;
    }
    
    std::string getName(){ return m_name; }
    std::vector<Vertex>& getVertices(){ return m_vertices; };
    std::vector<GLuint>& getIndices(){ return m_elements; };
    std::vector<Texture>& getTextures(){ return m_textures; };
    
    void addChild(Mesh* mesh){
        m_children.push_back(mesh);
    }
    
    void addChildren(Mesh* source){
        for(auto& child : source->getChildren()) addChild(child);
    }
    
    void addChildren(std::vector<Mesh*>& source){
        for(auto& child : source) addChild(child);
    }
    
    std::vector<Mesh*>& getChildren(){ return m_children; }
    
    void addTexture(Texture& texture){
        m_textures.push_back(texture);
        for(auto& mesh : m_children) mesh->addTexture(texture);
    }
    
    MaterialBase* getMaterial(){
        return material;
    }
    
    int size(){
        return (int) m_children.size();
    }

private:
    
    //Core
    std::string m_name;
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_elements;
    std::vector<Texture> m_textures;
    
    //Buffers
    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
    
    //Draw type
    GLenum m_usage;
    
    //Matrix
    glm::mat4 m_modelMatrix = glm::mat4(1.0f);
    glm::vec3 m_position = glm::vec3(1.0f);
    glm::vec3 m_scale = glm::vec3(1.0f);
    glm::vec3 m_rotation = glm::vec3(1.0f);
    DrawMode m_drawMode = DrawMode::DEFAULT;
    
    glm::mat4 getModelMatrix(){
        return m_modelMatrix;
    }
    
    void setModelMatrix(glm::mat4 model){
        m_modelMatrix = model;
    }

    
    //Materials
    SolidMaterial* m_wireMaterial = nullptr;
    MaterialBase* material = nullptr;
    void setWireMaterial(glm::vec3 color = Color::Green);
    
    //Children
    std::vector<Mesh*> m_children;
};

#endif /* Mesh_hpp */
