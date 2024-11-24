//
//  Rectangle.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 28/09/2024.
//

#ifndef Hexagon_hpp
#define Hexagon_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <vector>

#include "../Mesh/Vertex.h"
#include "../Mesh/Mesh.hpp"
#include "../Material/Texture.hpp"
#include "./Model.h"

class Hexagon : public Model{
    
public:
    
    Hexagon();
    ~Hexagon(){};
    
    std::vector<Vertex> vertices;
    std::vector<VertexElement> elements;

};

#endif /* Rectangle_hpp */
