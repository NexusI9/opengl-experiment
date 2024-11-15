//
//  VertexGroup.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 11/11/2024.
//

#include "VertexGroup.hpp"
#include <iostream>


void VertexGroup::addGroup(std::string name, VertexList vertices){
    VertexLayer temp = { .name = name };
    for(int i = 0; i < vertices.size(); i++) temp.points.push_back({ .vertex = vertices[i] });
    m_groups.push_back(temp);
}

void VertexGroup::bridge(){
    
    /**
     Bridge each group serially from 0 to end.
     */
    int index = 0;
    for(int g = 0; g < m_groups.size() - 1; g++){
        VertexLayer& current = m_groups[g];
        VertexLayer& next = m_groups[g + 1];
        
        for(auto& outerPoint : next.points){
            //Add point A & C (on next loop)
            
            //Add to cache
            outerPoint.index.push_back(index);
            
            //Add to global array
            m_elements.push_back(index);
            m_vertices.push_back(outerPoint.vertex);
            
            index++;
            
            //get closest inner point
            VertexGroupPoint closestPoint = current.points[0];
            for(auto& innerPoint : current.points){
                float newDistance = glm::distance(innerPoint.vertex.position, outerPoint.vertex.position);
                float closestDistance = glm::distance(closestPoint.vertex.position, outerPoint.vertex.position);
                if(newDistance < closestDistance) closestPoint = innerPoint;
            }
            
            //Add point B (opposite side)
            closestPoint.index.push_back(index);
            
            //Add to global array
            m_elements.push_back(index);
            m_vertices.push_back(closestPoint.vertex);
            
            index++;
            
        }
        
    }
    
}

VertexList VertexGroup::getVertex(){
    VertexList temp;
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
