//
//  Loader.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 05/10/2024.
//

#ifndef Model_h
#define Model_h

#include <stdio.h>
#include <vector>
#include "../Mesh/Vertex.h"

class Model{
  
public:
    
    Model(){};
    virtual ~Model(){};
    
    std::vector<Vertex> vertices;
    std::vector<VertexElement> elements;
    
};

#endif /* Loader_hpp */
