//
//  VertexList.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 10/11/2024.
//

#include "VertexList.hpp"
#include "../Utility/Debugger.hpp"
#include <algorithm>
#include <cstdlib>
#include <iterator>


//TODO: implement a VertexList object instead of using static utilities
void VertexList::scale(float scale){
    
    //get center
    glm::vec3 center;
    for(auto& vert : m_data) center += vert.position;
    center /= static_cast<float>(m_data.size());
    
    //scale towards or outwards this center
    for(auto& vert : m_data) vert.position = center + (vert.position - center) * scale;

}

void VertexList::translate(glm::vec3 translation){
    for(auto& vert : m_data) vert.position += translation;
}

void VertexList::subdivide(int amount){
    
    
}

void VertexList::decimate(int amount){
   
    std::vector<Vertex> tempVert;
    
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
        Vertex current = m_data[v];
        Vertex next = m_data[ (v+1) % m_data.size() ];
        avgDistance += glm::distance(current.position, next.position);
    }
    
    avgDistance /= m_data.size();
    
    //Generate Cluster
    std::vector<VertexCluster> cluster;
    float threshold = 0.1f;
    
    while(cluster.size() != amount){
        
        cluster.clear();
        
        for(v = 0; v < m_data.size(); ++v){
            
            Vertex current = m_data[v];
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
        tempVert.push_back(avgVert);
    }
    
    m_data = tempVert;
}

void VertexList::smooth(float amount){
 
    
}

void VertexList::noise(glm::vec3 amplitude){
    
    for(auto& vert : m_data){
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        r = (r > 0.5) ? r : -1.0f * r;
        vert.position.x += sin(r * amplitude.x);
        vert.position.y += cos(r * amplitude.y);
        vert.position.z += cos(r * amplitude.z);
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
