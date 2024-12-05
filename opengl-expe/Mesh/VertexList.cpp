//
//  VertexList.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 10/11/2024.
//

#include "VertexList.hpp"
#include "../Utility/Debugger.hpp"
#include "../Utility/Math/Perlin.h"

#include <algorithm>
#include <cstdlib>
#include <iterator>


//TODO: implement a VertexList object instead of using static utilities
void VertexList::scale(float scale){
    
    //get center
    glm::vec3 ctr = center();
    //scale towards or outwards this center
    for(auto& vert : m_data) vert.vertex.position = ctr + (vert.vertex.position - ctr) * scale;

}

void VertexList::translate(glm::vec3 translation){
    for(auto& vert : m_data) vert.vertex.position += translation;
}

void VertexList::subdivide(int amount){
    
    
}

void VertexList::decimate(int amount){
   
    std::vector<VertexList::Point> tempVert;
    
    //make sure its not reductible polygon
    if(m_data.size() < 4){ return; }
    
    //make sure amount isn't superior to current size
    int minAmount = static_cast<int>(m_data.size());
    amount = std::min(amount, minAmount - 1);
    
    /**
     1. Get average length between points
     2. Compare points between them to detect potential cluster
     3. If cluster number != target : tweak avg distance (dichotomy-like)
    */
    
    //Get average Distance
    float avgDistance = 0.0f;
    int v = 0;
    for(v = 0; v < m_data.size(); v++){
        Vertex current = m_data[v].vertex;
        Vertex next = m_data[ (v+1) % m_data.size() ].vertex;
        avgDistance += glm::distance(current.position, next.position);
    }
    
    avgDistance /= m_data.size();
    
    //Generate Cluster
    std::vector<VertexArray> cluster;
    float threshold = 0.1f;
    
    while(cluster.size() != amount){
        
        cluster.clear();
        
        for(v = 0; v < m_data.size(); ++v){
            
            Vertex current = m_data[v].vertex;
            bool added = false;
            
            for(auto& cl : cluster){
                if(glm::distance(current.position, cl.back().position) <= avgDistance){
                    cl.push_back(current);
                    added = true;
                    break;
                }
            }
            
            if(!added) cluster.push_back({ current });
        }
        
        if(cluster.size() < amount) avgDistance -= threshold;
        else avgDistance += threshold;
    }
    
    //Average Cluster vertices to one centroid point
    for(auto& cl : cluster){
        Vertex avgVert = cl[0];
        for(auto& vert : cl) avgVert += vert;
        avgVert /= static_cast<float>(cl.size()) + 1.0f;
        tempVert.push_back({.vertex = avgVert, .index = static_cast<VertexElement>(tempVert.size())});
    }
    
    m_data = tempVert;
}

void VertexList::smooth(float amount){
 
    
}

void VertexList::noise(glm::vec3 amplitude){
    
    glm::vec3 ctr = center();
    
    for(auto& vert : m_data){
        
        glm::vec3 offset = vert.vertex.position - ctr;
    
        float n = perlin::noise(offset.x, offset.y);
        offset.x += n * amplitude.x;
        offset.y += n * amplitude.y;
        offset.z += n * amplitude.z;
        
        vert.vertex.position = ctr + offset;
    }
    
}


void VertexList::simplify(){
    
}

void VertexList::concat(std::vector<VertexList>& sources){
    for(auto& list : sources) concat(list);
}

void VertexList::concat(VertexList& source){
    m_data.insert(
                       m_data.end(),
                       std::make_move_iterator(source.begin()),
                       std::make_move_iterator(source.end())
                       );
}


glm::vec3 VertexList::center(){
    glm::vec3 center = glm::vec3(0.0f);
    for(auto& vert : m_data) center += vert.vertex.position;
    center /= static_cast<float>(m_data.size());
    return center;
}

glm::vec3 VertexList::min(){
    glm::vec3 min = glm::vec3(INFINITY);
    for(auto& vert : m_data){
        min = glm::vec3(std::min(min.x, vert.vertex.position.x),
                        std::min(min.y, vert.vertex.position.y),
                        std::min(min.z, vert.vertex.position.z));
    }
    return min;
}

glm::vec3 VertexList::max(){
    glm::vec3 max = glm::vec3(-1.0 * INFINITY);
    for(auto& vert : m_data){
        max = glm::vec3(std::max(max.x, vert.vertex.position.x),
                        std::max(max.y, vert.vertex.position.y),
                        std::max(max.z, vert.vertex.position.z));
    }
    return max;
}

std::vector<glm::vec2> VertexList::toVec2(){
    std::vector<glm::vec2> temp;
    for(auto& [vertex, index] : m_data) temp.push_back(glm::vec2(vertex.position.x, vertex.position.y));
    return temp;
}


std::vector<double> VertexList::toDouble(bool x, bool y, bool z){

    std::vector<double> temp;
    for(auto& [vertex, index] : m_data){
        glm::vec3 pos = vertex.position;
        if( x ) temp.push_back( static_cast<double>(pos.x) );
        if( y ) temp.push_back( static_cast<double>(pos.y) );
        if( z ) temp.push_back( static_cast<double>(pos.z) );
    }
    return temp;
}


Vertex VertexList::average(){
    Vertex avg;
    avg.zero();
    for(auto& point : m_data) avg += point.vertex;
    avg /= static_cast<int>(m_data.size());
    return avg;
}
