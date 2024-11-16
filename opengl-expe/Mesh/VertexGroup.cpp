//
//  VertexGroup.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 11/11/2024.
//

#include "VertexGroup.hpp"
#include <iostream>


void VertexGroup::addGroup(std::string name, VertexList vertices){
    
    //get offset count
    VertexElement indexOffset = 0;
    for(auto& group : m_groups) indexOffset += group.points.size();
    
    //create new group
    VertexLayer temp = { .name = name };
    for(VertexElement i = 0; i < vertices.size(); i++){
        temp.points.push_back({ .vertex = vertices[i], .index = indexOffset + i });
    }
    
    m_groups.push_back(temp);
}

void VertexGroup::bridge(){
    
    /**
     Bridge each group serially from 0 to end.
     */
    for(int g = 0; g < m_groups.size() - 1; g++){
        
        //smaller loop
        VertexLayer& inner = m_groups[g].points.size() < m_groups[g + 1].points.size() ? m_groups[g] : m_groups[g + 1];
        //bigger loop
        VertexLayer& outer = m_groups[g].points.size() > m_groups[g + 1].points.size() ? m_groups[g] : m_groups[g + 1];
        
        for(int o = 0; o < outer.points.size(); o ++){
            
            VertexGroupPoint outerPoint = outer.points[o];

            /*
             Opposite completion:
             First compare the distance between the next outer and inner point, and get the closest to avoid too thin and long triangles. (C)
             Then if it's the inner that's closer, then create a new trangle with outer circle index + 1
                  
             1. Join A -> B -> C (cause closer to D)
                  B—C
                 / /
                 A——————D
             
             2. Create opposite triangle A -> C -> D
                 B—C._
                / /   \
                A——————D
             */
            
            
        
        
            //edge case for end of vertex loop
            if(o == outer.points.size() - 1){
                
                //end loop triangle
                m_elements.push_back(outerPoint.index);
                m_elements.push_back(inner.points.front().index);
                m_elements.push_back(outer.points.front().index);
                
            }else{
                

                VertexGroupPoint innerPoint = (o == 0) ? inner.points.front() : outer.points[0];
                //get closest inner point
                if(o > 0){
                    for(int i = 0; i < inner.points.size(); i++){
                        
                        VertexGroupPoint currentPoint = inner.points[i];
                        
                        float newDistance = glm::distance(currentPoint.vertex.position, outerPoint.vertex.position);
                        float closestDistance = glm::distance(innerPoint.vertex.position, outerPoint.vertex.position);
                        
                        if(newDistance < closestDistance) innerPoint = currentPoint;
                    }
                }
                
                //get next vertex
                VertexGroupPoint outerNext = outer.points[ (o+1) % outer.points.size() ];
                VertexGroupPoint innerNext = inner.points[ (innerPoint.index+1) % inner.points.size() ];

                //get A <-> D distance
                float outerDistance = glm::distance(outerPoint.vertex.position, outerNext.vertex.position);
                
                //get B <-> C distance
                float innerDistance = glm::distance(innerPoint.vertex.position, innerNext.vertex.position);
                
                VertexGroupPoint lastPoint = outerDistance < innerDistance ? outerNext : innerNext;
                
                m_elements.push_back(outerPoint.index); //Add first triangle point
                m_elements.push_back(innerPoint.index); //Add second triangle point
                m_elements.push_back(lastPoint.index); //Add third triangle point
                

                //Autocomplete opposite depending on distance configuration (A -> C -> D)
                if(outerDistance < innerDistance){
                    m_elements.push_back(outerNext.index);
                    m_elements.push_back(innerPoint.index);
                    m_elements.push_back(innerNext.index);
                }else{
                    m_elements.push_back(outerNext.index);
                    m_elements.push_back(outerPoint.index);
                    m_elements.push_back(innerNext.index);
                }
                
                std::cout << o << ":\t" << outerPoint.index << "\t" << innerPoint.index << "\t" << innerNext.index << std::endl;
        
            }
            
        }
        
    }
    
    
    std::reverse(m_elements.begin(), m_elements.end());
    
}

std::vector<Vertex> VertexGroup::getVertex(){
    std::vector<Vertex> temp;
    for(auto& group : m_groups){
        for(auto& point : group.points) temp.push_back(point.vertex);
    };
    return temp;
}


std::vector<VertexElement> VertexGroup::getElement(){
    return m_elements;
}

VertexLayer* VertexGroup::getGroup(std::string name){
    return nullptr;
}
