//
//  Mesh.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 01/09/2024.
//


#include <iostream>

#include "Mesh.hpp"
#include "../Utility/Utility.hpp"
#include "../Utility/Debugger.hpp"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> elements, std::vector<Texture> textures):
m_vertices(vertices),
m_elements(elements),
m_textures(textures){
    //Instantiate our buffers and array object and load data in it
    //We then proceed to layout the VAO data only when loading the Shader

    //Vertex Array Object (define how to interpret vbo data)
    m_vao.bind();
    
    //Vertex buffer Array (simply buffer the vertex data))
    m_vbo.setData(m_vertices);

    //Elements array
    m_ebo.setData(m_elements);
    
    m_vao.unbind();
    m_vbo.unbind();
    m_ebo.unbind();
    
};

Mesh::~Mesh(){
    delete shader;
}

void Mesh::loadShader(const std::string& vertShader, const std::string& fragShader, const std::string& fragName){
        
    const char* cVertShader = vertShader.c_str();
    const char* cFragShader = fragShader.c_str();
    const char* cFragName = fragName.c_str();
    
    shader = new Shader(cVertShader, cFragShader, cFragName);
    
    //map out the VAO data into our shader
    
    /*
     By default we will the the following location order:
     0: position    (vec3)
     1: normal      (vec3)
     2: color       (vec3)
     3: uv          (vec2)
     our reference point is the Vertex structure
     */
    
    shader->setAttribute(m_vao, m_vbo, "position", 3, sizeof(Vertex), (void*) 0);
    shader->setAttribute(m_vao, m_vbo, "normal", 3, sizeof(Vertex), (void*)( 3 * sizeof(float)));
    shader->setAttribute(m_vao, m_vbo, "color", 3, sizeof(Vertex), (void*)( 6 *  sizeof(float)));
    shader->setAttribute(m_vao, m_vbo, "uv", 2, sizeof(Vertex), (void*)( 9 * sizeof(float)));
    shader->use();

}

void Mesh::draw(Camera &camera, glm::mat4 matrix, glm::vec3 translation, glm::quat rotation, glm::vec3 scale){
    
    if(shader == nullptr){
        Debugger::print("No shader were found, mesh won't be rendered.", Verbose::Flag::MESH);
        return;
    }

    shader->use();
    shader->setUniformBlock("Camera", camera.getMatrixBindingIndex());
    shader->setMatrix4("model", matrix);
    
    //Apply texture to shader
    for(int t = 0; t < m_textures.size(); t++){
        m_textures[t].bind();
        shader->setSampler2D("texture"+std::to_string(t), t);
    }
     
    
    m_vao.bind();
    m_ebo.bind(); //VAO doesn't store ebo, so need to bind it during drawing phase

    //std::cout<< m_elements.size() <<std::endl;
    glDrawElements(GL_TRIANGLES, (int) m_elements.size(), GL_UNSIGNED_INT, 0);
    m_vao.unbind();
    
}

std::vector<GLuint> Mesh::getIndices(){
    return m_elements;
}




