//
//  MeshUtils.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 10/11/2024.
//

#include "MeshUtils.hpp"
#include "./Debugger.hpp"
#include <algorithm>

void MeshUtils::scale(std::vector<Vertex>& vertex, float scale){
    
    //get center
    glm::vec3 center;
    for(auto& vert : vertex) center += vert.position;
    center /= static_cast<float>(vertex.size());
    
    //scale towards or outwards this center
    for(auto& vert : vertex) vert.position = center + (vert.position - center) * scale;

}

void MeshUtils::subdivide(std::vector<Vertex>& vertex, int amount){
    
    
}

void MeshUtils::decimate(std::vector<Vertex>& vertex, int amount, DecimateType type){
   
    std::vector<Vertex> tempVert;
    
    //make sure amount isn't superior to current size
    int minAmount = static_cast<int>(vertex.size());
    amount = std::min(amount, minAmount - 1);
    
    //edge case: check if unregular shape, if regular shape like circle, then switch to uniform
    float div = 0.0f;
    for(int i = 0; i < vertex.size(); i++){
        glm::vec3 current = vertex[i].position;
        glm::vec3 next = vertex[ (i+1) % vertex.size() ].position;
        div = (i == 0) ? glm::distance(current, next) : glm::distance(current, next) / div;
    }
    
    //means all edges have the same distance between each other, thus no need for proximity method, force UNIFORM
    type = (div == 1) ? DecimateType::UNIFORM : type;
    
    switch(type){
        
        //TODO: fix Promiximity approach
        case DecimateType::PROXIMITY: {
            
            //Proximity Decimation: Decimate the mesh based of vertex position proximity (distance)
            float maxDistance = 3.0f; //max distance threshold
            float threshold = 0.1f; //step to substract or add to threshold if vertex count doesn't meet the target number
            
            while(tempVert.size() != amount){
                
                std::cout << "\n\n" << tempVert.size() << " : " << amount << std::endl;
                tempVert.clear();
                int step = 1;
                
                //group depending on threshold
                for(int i = 0; i < vertex.size(); i += step){
                    
                    //get current and next points
                    Vertex currentPoint = vertex[i];
                    Vertex nextPoint = vertex[i+1];
                    
                    //Get previous and next point distance
                    float nextDistance = glm::distance(currentPoint.position, nextPoint.position);
                    
                    Vertex avgPoints = currentPoint;
                    
                    //If next point distance meet threshold, add to average, and skip it
                    if(nextDistance < maxDistance){
                        avgPoints += nextPoint;
                        avgPoints /= 2;
                        step = 2;
                    }else{
                        step = 1;
                    }
                    
                    //replace index with new average point
                    tempVert.push_back(avgPoints);
                    
                }
                
                if(tempVert.size() < amount) maxDistance -= threshold;
                else maxDistance += threshold;
                
            }
            
            break;
        }
            
        case DecimateType::UNIFORM:{
            int step = static_cast<int>(vertex.size()/amount);
            //Average Decimation: Uniformly and "linearly" decimate the mesh based of vertex index
            for(int i = 0; i < amount; i++){
                Vertex avgVertex = vertex[i];
                int s = i;
                while(s < i + step){
                    avgVertex += vertex[s];
                    s++;
                }
                avgVertex /= static_cast<float>(step);
                tempVert.push_back(avgVertex);
            }
            break;
        }
    }
    
    vertex = tempVert;
}

void MeshUtils::smooth(std::vector<Vertex>& vertex, float amount){
 
    
}

void MeshUtils::noise(std::vector<Vertex>& vertex, float amplitude){
    
    
}


void MeshUtils::simplify(std::vector<Vertex>& vertex){
    
}
