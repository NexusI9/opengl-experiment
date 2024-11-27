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
#include "../Utility/Transform.hpp"
#include "../Utility/Color.h"


Mesh::Mesh(const MeshArgsVertex& args):
GameObject(Type::OBJECT),
m_vertices(args.vertices),
m_elements(args.elements),
m_textures(args.textures),
m_name(args.name){
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
    
    printf("%s \t %i", m_name.c_str(), (int)m_elements.size());
    
    setDrawMode(DrawMode::DEFAULT);
};


Mesh::Mesh(const MeshArgsBuffer& args):
GameObject(Type::OBJECT),
m_vao(args.vao),
m_vbo(args.vbo),
m_ebo(args.ebo),
m_textures(args.textures),
m_name(args.name){
    setDrawMode(DrawMode::DEFAULT);
};

Mesh::Mesh(const MeshArgsModel& args):
GameObject(Type::OBJECT),
m_vertices(args.model.vertices),
m_elements(args.model.elements),
m_name(args.name){
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
    
    setDrawMode(DrawMode::DEFAULT);
};


void Mesh::onDraw(Camera& camera){
    
    //cancel if empty elements or empty children
    if(m_elements.size() == 0 && m_children.size() == 0){ return; }
    
    //draw material if existing
    if(material!=nullptr) material->onDraw(camera, m_modelMatrix);
    else Debugger::print("No material set, some mesh will be missing");
    
    m_vao.bind();
    m_ebo.bind(); //VAO doesn't store ebo, so need to bind it during drawing phase

    //Point drawing
    if(m_drawMode == DrawMode::POINTS){
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glDrawElements(GL_POINTS, (int) m_elements.size(), GL_UNSIGNED_INT, 0);
        
    //Wireframe drawing
    }else if(m_drawMode == DrawMode::WIREFRAME){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_LINES, (int) m_elements.size(), GL_UNSIGNED_INT, 0);
    
    //Default + Debug drawing
    }else{
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, (int) m_elements.size(), GL_UNSIGNED_INT, 0);
        if(m_drawMode == DrawMode::DEBUGGER){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawElements(GL_POINTS, (int) m_elements.size(), GL_UNSIGNED_INT, 0);
        }
    }
    
    m_vao.unbind();
    m_ebo.unbind();
    
    //Update children
    for(auto& mesh : m_children) mesh->onDraw(camera);
    
}

void Mesh::onInput(SDL_Event& event){
    
    //Update children
    for(auto& mesh : m_children) mesh->onInput(event);
}


void Mesh::setMaterial(const MaterialBase& mat){
    material = mat.clone();
    //If material doesn't have any shader, init material from mesh vao, vbo...
    if(material->getShader() == nullptr) material->init(m_vao, m_vbo, m_textures);
    
    //Update children
    for(auto& mesh : m_children) mesh->setMaterial(mat);
}

void Mesh::setDrawMode(DrawMode mode){
    
    m_drawMode = mode;
    
    switch(mode){
        case DrawMode::WIREFRAME:
        case DrawMode::DEBUGGER:
        case DrawMode::POINTS:
            setWireMaterial();
            break;
            
        case DrawMode::DEFAULT:
        default:
            //if(material) setMaterial(material); //set back material
            break;
    }
    
    //Update children
    for(auto& mesh : m_children) mesh->setDrawMode(mode);
    
}

void Mesh::setPosition(float x, float y, float z){
    m_position = glm::vec3(x,y,z);
    setModelMatrix(Transform::translate(x, y, z));
    
    //Update children
    for(auto& mesh : m_children){
        //get current mesh matrix
        glm::mat4 meshMatrix = mesh->getModelMatrix();
        //multiply the original mesh position to the new one to not overriding it
        mesh->setModelMatrix(meshMatrix * Transform::translate(x,y,z));
    };
}

void Mesh::setRotation(float degree, float x, float y, float z){
    m_rotation = glm::vec3(x,y,z);
    setModelMatrix(Transform::rotate(degree, x, y, z));
    
    //Update children
    for(auto& mesh : m_children){
        glm::mat4 meshMatrix = mesh->getModelMatrix();
        mesh->setModelMatrix(meshMatrix * Transform::rotate(degree, x, y, z));
    };
}

void Mesh::setScale(float x, float y, float z){
    m_scale = glm::vec3(x,y,z);
    setModelMatrix(Transform::scale(x, y, z));
    
    //Update children
    for(auto& mesh : m_children){
        glm::mat4 meshMatrix = mesh->getModelMatrix();
        mesh->setModelMatrix(meshMatrix * Transform::scale(x, y, z));
    };
}

void Mesh::setScale(float value){
    m_scale = glm::vec3(value,value,value);
    setModelMatrix(Transform::scale(value,value,value));
    
    //Update children
    for(auto& mesh : m_children){
        glm::mat4 meshMatrix = mesh->getModelMatrix();
        mesh->setModelMatrix(meshMatrix * Transform::scale(value, value, value));
    };
}

void Mesh::lookAt(float x, float y, float z){
    setModelMatrix(Transform::lookAt(m_position, glm::vec3(x,y,z)));
    
    for(auto& mesh : m_children){
        //get current mesh matrix
        glm::mat4 meshMatrix = mesh->getModelMatrix();
        glm::vec3 meshPosition = mesh->getPosition();
        //multiply the original mesh position to the new one to not overriding it
        mesh->setModelMatrix(meshMatrix * Transform::lookAt(meshPosition,glm::vec3(x,y,z)));
    };
}

void Mesh::setWireMaterial(glm::vec3 color){
    if(m_wireMaterial) m_wireMaterial->setColor(color);
    else m_wireMaterial = new SolidMaterial({.color = color});
    material = m_wireMaterial;
    material->init(m_vao, m_vbo, m_textures);
}
