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


using VertexCluster = std::vector<Vertex>;

enum class DecimateType{
    UNIFORM,
    PROXIMITY
};

class MeshUtils{
  
public:
    
    static void scale(std::vector<Vertex>& vertex, float scale);
    static void subdivide(std::vector<Vertex>& vertex, int amount);
    static void decimate(std::vector<Vertex>& vertex, int amount, DecimateType type = DecimateType::UNIFORM);
    static void smooth(std::vector<Vertex>& vertex, float amount);
    static void noise(std::vector<Vertex>& vertex, float amplitude);
    static void simplify(std::vector<Vertex>& vertex);
    
private:
    
};

#endif /* MeshUtils_hpp */
