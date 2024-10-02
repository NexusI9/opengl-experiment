//
//  Rectangle.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 28/09/2024.
//

#include "Rectangle.hpp"
#include <glm/glm.hpp>
#include <iostream>
#include "../Utility/Constant.h"


Rectangle::Rectangle() : BaseObject(Type::OBJECT){
    
    std::vector<glm::vec3> positions{
        glm::vec3(-0.5f,  0.5f,   0.0f),
        glm::vec3(0.5f,   0.5f,   0.0f),
        glm::vec3(0.5f,   -0.5f,  0.0f),
        glm::vec3(-0.5f,  -0.5f,  0.0f)
    };
    
    
    std::vector<glm::vec3> normals{
        glm::vec3(0.0f,  0.0f,   1.0f),
        glm::vec3(0.0f,  0.0f,   1.0f),
        glm::vec3(0.0f,  0.0f,   1.0f),
        glm::vec3(0.0f,  0.0f,   1.0f)
    };
    
    std::vector<glm::vec3> colors{
        glm::vec3(1.0f,  0.0f,   0.0f),
        glm::vec3(0.0f,  1.0f,   0.0f),
        glm::vec3(0.0f,  0.0f,   1.0f),
        glm::vec3(1.0f,  1.0f,   1.0f)
    };
    
    
    std::vector<glm::vec2> uv{
        glm::vec2(0.0f,  0.0f),
        glm::vec2(1.0f,  0.0f),
        glm::vec2(1.0f,  1.0f),
        glm::vec2(0.0f,  1.0f)
    };
    

    for (size_t i = 0; i < positions.size(); ++i) {
        Vertex tempVertex;
        tempVertex.position = positions[i];
        tempVertex.normal = normals[i];
        tempVertex.color = colors[i];
        tempVertex.texUV = uv[i];
        m_vertices.push_back(tempVertex);
    }


    
    m_elements = {0, 1, 2, 2, 3, 0};
    
    m_mesh = new Mesh(m_vertices, m_elements, m_textures);
    
    const std::string vertShaderPath = ROOT_DIR + "Shader/default.vert";
    const std::string fragShaderPath = ROOT_DIR + "Shader/default.frag";
    
    m_mesh->loadShader(vertShaderPath, fragShaderPath, "outColor");
    
}

Rectangle::~Rectangle(){}



void Rectangle::draw(Camera& camera){

    if(m_mesh) m_mesh->draw(
                            camera,
                            glm::mat4(1.0f),
                            glm::vec3(0.0f),
                            glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
                            glm::vec3(1.0f)
                            );
}