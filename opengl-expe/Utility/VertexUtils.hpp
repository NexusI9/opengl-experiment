//
//  MeshUtils.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 10/11/2024.
//

#ifndef MeshUtils_hpp
#define MeshUtils_hpp

#include <stdio.h>
#include <vector>
#include <glm/glm.hpp>
#include "../Mesh/Vertex.h"

class VertexUtils{
  
public:
    //Transformation modifiers
    static void scale(VertexList& vertex, float scale);
    static void translate(VertexList& vertex, glm::vec3 translation);
    
    //Optimization modifiers
    static void subdivide(VertexList& vertex, int amount);
    static void decimate(VertexList& vertex, int amount);
    static void simplify(VertexList& vertex);
    
    //Deformation modifiers
    static void smooth(VertexList& vertex, float amount);
    static void noise(VertexList& vertex, glm::vec3 amplitude = glm::vec3(1.0f, 1.0f, 1.0f));
    
    //Organization modifiers
    static void concat(VertexList& destination, std::vector<VertexList>& sources);
    static void concat(VertexList& destination, VertexList& source);
    
private:
    
};

#endif /* MeshUtils_hpp */
