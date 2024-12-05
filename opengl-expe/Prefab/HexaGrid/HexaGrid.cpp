//
//  Grid.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 23/11/2024.
//

#include "HexaGrid.hpp"
#include "../../Utility/Vector.h"

HexaGrid::HexaGrid(const HexaGridArgs& args) :
    m_dimension(args.dimension.x, args.dimension.y),
    m_radius(args.radius),
    m_innerRadius(args.radius * sqrt(3.0f)/2.0f),
    m_perimeter(args.perimeter)
{
    build();
}

HexaTile HexaGrid::addTile(CubeCoordinate origin, CubeCoordinate direction){
    return{
        .cubeCoordinate = origin + direction
    };
}

void HexaGrid::drawGrid(std::vector<glm::vec3>& instances){
    
    CubeCoordinate yOffset;

    glm::vec3 worldOffset(-1.0f * (m_dimension.y * m_radius) / (1.0f + m_radius * 2.0f ), (m_dimension.x * m_radius) / (1.0f + m_radius / 2.0f ), 0.0f );
    
    for(int y = 0; y < m_dimension.y; y++){
        for(int x = 0; x < m_dimension.x; x++){
            
            CubeCoordinate newCoordinate{ x, 0, -1 * x };
            newCoordinate += yOffset; //Move on Y axis
            newCoordinate += CubeDirection::EAST; // Move on X Axis
            
            glm::vec3 worldCoordinate = toWorldCoordinate(newCoordinate, worldOffset);
            
            //Check if world coordinate are within perimeter
            if((m_perimeter.size() > 0
                && isInside(glm::vec2(worldCoordinate.x, worldCoordinate.y), m_perimeter.toVec2()))
               || m_perimeter.size() == 0){
                //Store coordinate in member cache
                m_tiles.push_back({
                    .cubeCoordinate = newCoordinate,
                    .worldCoordinate = worldCoordinate,
                    .radius = m_radius
                });
                
                //Store world position in VBO vector
                instances.push_back(worldCoordinate);
            }
            
            
        }
        
        yOffset += (y % 2 == 0) ? CubeDirection::NORTH_WEST : CubeDirection::NORTH_EAST;
    }

}

Dimension HexaGrid::dimFromPerimeter(){
    
    glm::vec3 minVertex = m_perimeter.min();
    glm::vec3 maxVertex = m_perimeter.max();
    
    printf("min: %f, %f,%f\nmax: %f,%f,%f\n", minVertex.x, minVertex.y, minVertex.z, maxVertex.x, maxVertex.y, maxVertex.z);
    
    glm::vec2 dist( std::abs(minVertex.x - maxVertex.x), std::abs(minVertex.y - maxVertex.y));
    Dimension dim( std::floor(  dist.x / m_radius ), std::floor(  dist.y / m_radius ));

    if(dim.x <= 1 || dim.y <= 1){
        std::cout << "WARNING: Hexagon radius too large for the perimeter." << std::endl;
    }
    
    return dim;
    
}

void HexaGrid::build(){
        
    //Calculate positions
    std::vector<glm::vec3> vboCoordinate;
    
    //Generate dimension based on perimeter
    if(m_perimeter.size() > 0) m_dimension = dimFromPerimeter();
    
    //Generate grid
    drawGrid(vboCoordinate);

    //Instance new mesh and setup shader with instance vbo
    Hexagon hexagon({
        .innerColor = Color::Black,
        .outerColor = Color::White,
        .radius = m_radius
    });
    
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
    return glm::vec3(y,x,z) + origin;
}
