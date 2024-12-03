//
//  Grid.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 23/11/2024.
//

#include "HexaGrid.hpp"

HexaGrid::HexaGrid(int x, int y, const HexUnit radius) :
    m_radius(radius),
    m_innerRadius(radius * sqrt(3.0f)/2.0f){
    m_dimension.x = x;
    m_dimension.y = y;
    build();
    
}

HexaTile HexaGrid::addTile(CubeCoordinate origin, CubeCoordinate direction){
    return{
        .cubeCoordinate = origin + direction
    };
}

void HexaGrid::build(){
        
    //Calculate positions
    CubeCoordinate yOffset;
    std::vector<glm::vec3> vboCoordinate;
    for(int y = 0; y < m_dimension.y; y++){
        for(int x = 0; x < m_dimension.x; x++){
            
            CubeCoordinate newCoordinate{ x, 0, -1 * x };
            newCoordinate += yOffset; //Move on Y axis
            newCoordinate += CubeDirection::EAST; // Move on X Axis
            
            glm::vec3 worldCoordinate = toWorldCoordinate(newCoordinate);
            
            //Store coordinate in member cache
            m_tiles.push_back({
                .cubeCoordinate = newCoordinate,
                .worldCoordinate = worldCoordinate,
                .radius = m_radius
            });
            
            //Store world position in VBO vector
            vboCoordinate.push_back(worldCoordinate);
            
        }
        
        yOffset += (y % 2 == 0) ? CubeDirection::NORTH_WEST : CubeDirection::NORTH_EAST;
    }

    //Instance new mesh and setup shader with instance vbo
    Hexagon hexagon;
    m_mesh = new Mesh({ .name = "hexagrid", .model = hexagon });
    m_mesh->setDrawMode({
        .mode = Mesh::Draw::Mode::INSTANCE,
        .instances = static_cast<GLsizei>(vboCoordinate.size())
    });
    m_mesh->setMaterial(m_material); //"plug" Vertex buffers to Shader
    
    //Fill buffer and copy data so persistent throughout mesh lifetime (via VBO)
    VBO instanceBuffer;
    instanceBuffer.copyData( sizeof(glm::vec3) * vboCoordinate.size() , vboCoordinate.data());
    m_mesh->vbo.push("instances",  instanceBuffer);
    
    //Link shader buffers
    Shader* shader = m_mesh->getMaterial()->getShader();
    VBO* instanceVBO = m_mesh->vbo.find("instances");
    VBO meshVBO = m_mesh->vbo.origin();
    
    VAO vao = m_mesh->vao;
    
    if(shader && instanceVBO){
        
        //TODO: Find a way to make CustomShader more flexible, instead of having to retrive its shader to setup VBO/ VAO
        
        //Link mesh related attributes
        shader->setAttribute(vao, meshVBO, "position", 3, sizeof(Vertex), (void*) 0);
        shader->setAttribute(vao, meshVBO, "normal", 3, sizeof(Vertex), (void*)( 3 * sizeof(float)));
        shader->setAttribute(vao, meshVBO, "color", 3, sizeof(Vertex), (void*)( 6 *  sizeof(float)));
        shader->setAttribute(vao, meshVBO, "uv", 2, sizeof(Vertex), (void*)( 9 * sizeof(float)));
        
        //Link instance related attributes
        shader->setAttribute(vao, *instanceVBO, "worldCoordinate", 3, sizeof(glm::vec3), (void*)0);
        // Updates per instance, not per vertex
        shader->setAttributePerInstance(vao, "worldCoordinate", 1);

    }
    

}

glm::vec3 HexaGrid::toWorldCoordinate(CubeCoordinate coo, glm::vec3 origin){
    float compense = -1.0f * coo.r * m_innerRadius;
    float x = -2.0f * m_innerRadius * coo.q + compense;
    float y = -1.5f * m_radius * coo.r ;
    float z = 0.0f;
    return glm::vec3(y,x,z);
}
