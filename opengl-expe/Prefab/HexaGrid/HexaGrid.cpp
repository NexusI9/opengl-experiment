//
//  Grid.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 23/11/2024.
//

#include "HexaGrid.hpp"

HexaGrid::HexaGrid(glm::vec2 dimension, float size) : m_dimension(dimension), m_size(size){
    build();
    
}

HexaTile HexaGrid::addTile(CubeCoordinate origin, CubeCoordinate direction){
    return{
        .cubeCoordinate = origin + direction
    };
}

void HexaGrid::build(){

    
    /**
     Build the hexagone grid coordinate based on a top left origin
            +-------------------------------->
            |       +------------->
            |       |       ..
            |       |     /    \
            |       |     |     |
            |       |      \   /
            |      V
            V
     */
    
    m_VAO.bind();
    //Add base hexagon instance
    m_meshVBO.setData(hexagon.vertices);

    //Set hexagon vertices to location 0
    m_meshVBO.bind();
    
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    
    //normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)) );
    glEnableVertexAttribArray(1);
    
    //color
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3) * 2) );
    glEnableVertexAttribArray(2);
    
    //uv
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3) * 3) );
    glEnableVertexAttribArray(3);

    m_meshVBO.unbind();
    
    //Calculate positions
    CubeCoordinate yOffset;
    std::vector<glm::vec3> vboCoordinate;
    for(int y = 0; y < m_dimension.y; y++){
        for(int x = 0; x < m_dimension.x; x++){
            
            CubeCoordinate newCoordinate{ x, 0, -1 * x };
            newCoordinate += yOffset; //Move on Y axis
            newCoordinate += CubeDirection::WEST; // Move on X Axis
            
            glm::vec3 worldCoordinate = toWorldCoordinate(newCoordinate);
            
            //Store coordinate in member cache
            m_tiles.push_back({
                .cubeCoordinate = newCoordinate,
                .worldCoordinate = worldCoordinate,
                .size = m_size
            });
            
            //Store world position in VBO vector
            vboCoordinate.push_back(worldCoordinate);
            
        }
        
        yOffset += (y % 2 == 0) ? CubeDirection::SOUTH_EAST : CubeDirection::SOUTH_WEST;
    }
    
    m_instanceVBO.setData(sizeof(glm::vec3) * vboCoordinate.size(), vboCoordinate.data());
    
    //Set positions to location 1
    m_instanceVBO.bind();
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribDivisor(1, 1); // Updates per instance, not per vertex
    m_instanceVBO.unbind();
    
    m_VAO.unbind();
    
}

glm::vec3 HexaGrid::toWorldCoordinate(CubeCoordinate coo, glm::vec3 origin){
    float x =  (coo.q + ((coo.r%2 == 0) ? 0 : 0.5) ) * m_size;
    float y =  -1.0f * coo.s * m_size;
    float z = 0.0f;
    return glm::vec3(x,y,z) + origin;
}
