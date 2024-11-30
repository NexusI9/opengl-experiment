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
    vao.bind();
    
    //Vertex buffer Array (simply buffer the vertex data))
    vbo.origin().setData(m_vertices);

    //Elements array
    ebo.setData(m_elements);
    
    vao.unbind();
    vbo.origin().unbind();
    ebo.unbind();
    
    setDrawMode(m_drawMode);
};


Mesh::Mesh(const MeshArgsBuffer& args):
GameObject(Type::OBJECT),
m_textures(args.textures),
m_name(args.name){
    
    vao = args.vao;
    ebo = args.ebo;
    vbo.init(args.vbo);
    
    setDrawMode(m_drawMode);
};

Mesh::Mesh(const MeshArgsModel& args):
GameObject(Type::OBJECT),
m_vertices(args.model.vertices),
m_elements(args.model.elements),
m_name(args.name){
    //Instantiate our buffers and array object and load data in it
    //We then proceed to layout the VAO data only when loading the Shader

    //Vertex Array Object (define how to interpret vbo data)
    vao.bind();
    
    //Vertex buffer Array (simply buffer the vertex data))
    vbo.origin().setData(m_vertices);

    //Elements array
    ebo.setData(m_elements);
    
    vao.unbind();
    vbo.origin().unbind();
    ebo.unbind();
    
    setDrawMode(m_drawMode);
};


void Mesh::onDraw(Camera& camera){
    
    //cancel if empty elements or empty children
    if(m_elements.size() == 0 && m_children.size() == 0){ return; }
    
    //draw material if existing
    if(material!=nullptr) material->onDraw(camera, m_modelMatrix);
    else Debugger::print("No material set, some mesh will be missing");
    
    vao.bind();
    ebo.bind(); //VAO doesn't store ebo, so need to bind it during drawing phase
    
    switch(m_drawMode.mode){
        case  Draw::Mode::POINT:
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            glDrawElements(GL_POINTS, (int) m_elements.size(), GL_UNSIGNED_INT, 0);
            break;
        
        case Draw::Mode::WIREFRAME:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawElements(GL_LINES, (int) m_elements.size(), GL_UNSIGNED_INT, 0);
            break;
            
        case Draw::Mode::INSTANCE:
            glDrawElementsInstanced(
                GL_TRIANGLES, (int) m_elements.size(), GL_UNSIGNED_INT, 0, m_drawMode.instances
            );
            break;
            
        default:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDrawElements(GL_TRIANGLES, (int) m_elements.size(), GL_UNSIGNED_INT, 0);
            if(m_drawMode.mode == Draw::Mode::DEBUGGER){
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glDrawElements(GL_POINTS, (int) m_elements.size(), GL_UNSIGNED_INT, 0);
            }
    }

    
    vao.unbind();
    ebo.unbind();
    
    //Update children
    for(auto& mesh : m_children) mesh->onDraw(camera);
    
}

void Mesh::onInput(SDL_Event& event){
    
    //Update children
    for(auto& mesh : m_children) mesh->onInput(event);
}


void Mesh::setMaterial(const MaterialBase& mat){
    material = mat.clone();
    material->init(vao, vbo.origin(), m_textures);
    //Update children
    for(auto& mesh : m_children) mesh->setMaterial(mat);
}

void Mesh::setDrawMode(Draw mode){
    
    m_drawMode = mode;
    
    switch(m_drawMode.mode){
        case Draw::Mode::WIREFRAME:
        case Draw::Mode::DEBUGGER:
        case Draw::Mode::POINT:
            setWireMaterial();
            break;
            
        case Draw::Mode::DEFAULT:
        default:
            //if(material) setMaterial(material); //set back material
            break;
    }
    
    //Update children
    for(auto& mesh : m_children) mesh->setDrawMode(m_drawMode);
    
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
    material->init(vao, vbo.origin(), m_textures);
}
