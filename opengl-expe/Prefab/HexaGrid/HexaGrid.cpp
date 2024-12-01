//
//  Grid.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 23/11/2024.
//

#include "HexaGrid.hpp"

HexaGrid::HexaGrid(int x, int y, float radius) : m_radius(radius){
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
    //float x = (coo.q + ((coo.r%2 == 0) ? 0 : 0.5) ) * m_size;
    //float y = -1.0f * coo.s * m_size;
    //printf("%i\t%i\t%i\t\t%i\n", coo.q, coo.r, coo.s,coo.s%2);
    /**
     //float x = m_radius * (3.0f / 2.0f) * coo.q;                     // Horizontal spacing
     //float y = m_radius * sqrt(3.0f) * (coo.r + coo.q / 2.0f);
     float x = (coo.q + coo.r * 0.5f - coo.r / 2.0f) * innerRadius(m_radius) * 2.0f;
     float y = coo.r * m_radius * 1.5f;
     */
    float compense = -1.0f * coo.r * m_radius;
    float x = -1.0f * m_radius * coo.q + compense;
    float y = -1.0f * m_radius * coo.r ;
    float z = 0.0f;
    return glm::vec3(y,x,z);
}
