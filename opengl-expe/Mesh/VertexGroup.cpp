//
//  VertexGroup.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 11/11/2024.
//

#include "VertexGroup.hpp"



void VertexGroup::addGroup(std::string name, VertexList vertices){
    
    VertexLayer temp;
    for(int i = 0; i < vertices.size(); i++) temp.push_back({ .vertex = vertices[i], .index = i });
    m_groups[name] = temp;
    
}

void VertexGroup::bridge(){
    
    /**
     Bridge each group serially from 0 to end.
     */
    int index = 0;
    //for(auto &group : m_groups)
    
}

VertexList VertexGroup::getVertex(){
    VertexList temp;
    for(auto& [name, layer] : m_groups){
        for(auto& point : layer) temp.push_back(point.vertex);
    };
    return temp;
}


std::vector<VertexElement> VertexGroup::getElement(){

    std::vector<VertexElement> temp;
    for(auto& [name, layer] : m_groups){
        for(auto& point : layer) temp.push_back(point.index);
    }
    return temp;

}

VertexLayer* VertexGroup::getGroup(std::string name){
    return m_groups.find(name) != m_groups.end() ? &m_groups[name] : nullptr;
}
