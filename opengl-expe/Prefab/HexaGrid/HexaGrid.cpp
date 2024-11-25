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
    
    m_shader.setAttribute(m_vao, m_meshVBO, "position", 3, sizeof(Vertex), (void*) 0);
    m_shader.setAttribute(m_vao, m_meshVBO, "normal", 3, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
    m_shader.setAttribute(m_vao, m_meshVBO, "color", 3, sizeof(Vertex), (void*)( 2 * sizeof(glm::vec3)));
    m_shader.setAttribute(m_vao, m_meshVBO, "uv", 2, sizeof(Vertex), (void*)( 3 * sizeof(glm::vec3)));
    
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
    
    m_shader.setAttribute(m_vao, m_instanceVBO, "worldCoordinate", 3, sizeof(glm::vec3), (void*)0);
    // Updates per instance, not per vertex
    glVertexAttribDivisor(m_shader.getAttributeLocation("worldCoordinate"), 1);
    
    

}

glm::vec3 HexaGrid::toWorldCoordinate(CubeCoordinate coo, glm::vec3 origin){
    float x =  (coo.q + ((coo.r%2 == 0) ? 0 : 0.5) ) * m_size;
    float y =  -1.0f * coo.s * m_size;
    float z = 0.0f;
    return glm::vec3(x,y,z) + origin;
}
