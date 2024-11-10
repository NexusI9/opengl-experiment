//
//  VertexUtils.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 10/11/2024.
//

#include "VertexUtils.hpp"
#include "./Debugger.hpp"
#include <algorithm>
#include <cstdlib>
#include <iterator>


void VertexUtils::scale(VertexList& vertex, float scale){
    
    //get center
    glm::vec3 center;
    for(auto& vert : vertex) center += vert.position;
    center /= static_cast<float>(vertex.size());
    
    //scale towards or outwards this center
    for(auto& vert : vertex) vert.position = center + (vert.position - center) * scale;

}

void VertexUtils::translate(VertexList& vertex, glm::vec3 translation){
    for(auto& vert : vertex) vert.position += translation;
}

void VertexUtils::subdivide(VertexList& vertex, int amount){
    
    
}

void VertexUtils::decimate(VertexList& vertex, int amount){
   
    VertexList tempVert;
    
    //make sure its not reductible polygon
    if(vertex.size() < 4){ return; }
    
    //make sure amount isn't superior to current size
    int minAmount = static_cast<int>(vertex.size());
    amount = std::min(amount, minAmount - 1);
    
    /**
     1. Get average length between points
     2. Compare points between them to detect potential cluster
     3. If cluster number != target : tweak avg distance (dichotomy-like)
    */
    
    //Get average Distance
    float avgDistance = 0.0f;
    int v = 0;
    for(v = 0; v < vertex.size(); v++){
        Vertex current = vertex[v];
        Vertex next = vertex[ (v+1) % vertex.size() ];
        avgDistance += glm::distance(current.position, next.position);
    }
    
    avgDistance /= vertex.size();
    
    //Generate Cluster
    std::vector<VertexCluster> cluster;
    float threshold = 0.1f;
    
    while(cluster.size() != amount){
        
        cluster.clear();
        
        for(v = 0; v < vertex.size(); ++v){
            
            Vertex current = vertex[v];
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
    
    vertex = tempVert;
}

void VertexUtils::smooth(VertexList& vertex, float amount){
 
    
}

void VertexUtils::noise(VertexList& vertex, float amplitude){
    
    for(auto& vert : vertex){
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        r = (r > 0.5) ? r : -1.0f * r;
        vert.position.x += sin(r * amplitude);
        vert.position.y += cos(r * amplitude);
    }
    
}


void VertexUtils::simplify(VertexList& vertex){
    
}

void VertexUtils::concat(VertexList& destination, std::vector<VertexList>& sources){
    for(auto& list : sources) VertexUtils::concat(destination, list);
}

void VertexUtils::concat(VertexList& destination, VertexList& source){
    destination.insert(
                       destination.end(),
                       std::make_move_iterator(source.begin()),
                       std::make_move_iterator(source.end())
                       );
}
