//
//  Vector.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 05/12/2024.
//

#ifndef Vector_h
#define Vector_h
#include <glm/glm.hpp>
#include <cmath>
#include "../Mesh/VertexList.hpp"


/**
 Check if a point is within an area
 */
bool isInside(glm::vec2 point, std::vector<glm::vec2> polygon){
    
    bool inside = false;
    
    glm::vec2 p1, p2;
    
    for(int v = 0; v < polygon.size(); v++){
        
        p1 = glm::vec2(polygon[v]);
        p2 = glm::vec2(polygon[(v + 1) % polygon.size()]);
        
        if(point.y > std::min(p1.y, p2.y)
           && point.y <= std::max(p1.y, p2.y)
           && point.x <= std::max(p1.x, p2.x)){
            
            float intersection = (point.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;
            
            if(p1.x == p2.x || point.x < intersection) inside = !inside;
            
        }
        
    }
    
    return inside;
    
    
}


#endif /* Vector_h */

