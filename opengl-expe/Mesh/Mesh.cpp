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
#include "../Utility/Template.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> elements, std::vector<Texture> textures):
GameObject(Type::OBJECT),
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

Mesh::~Mesh(){}

void Mesh::draw(Camera& camera){
    
    if(!material){
        Debugger::print("No Material were found, so mesh might be missing");
        return;
    }
    
    material->draw(camera);
    
    m_vao.bind();
    m_ebo.bind(); //VAO doesn't store ebo, so need to bind it during drawing phase

    glDrawElements(GL_TRIANGLES, (int) m_elements.size(), GL_UNSIGNED_INT, 0);
    m_vao.unbind();
    m_ebo.unbind();
    
}


void Mesh::setMaterial(Material& mat){
    material = &mat;
    material->init(m_vao, m_vbo, m_vertices, m_textures);
}

std::vector<GLuint> Mesh::getIndices(){
    return m_elements;
}




