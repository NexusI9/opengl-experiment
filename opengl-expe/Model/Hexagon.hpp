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
#include "../Utility/Color.h"
#include "./Model.h"

struct HexagonArgs{
    const glm::vec3 outerColor = Color::White;
    const glm::vec3 innerColor = Color::White;
    const float radius = 1.0f;
};

class Hexagon : public Model{
    
public:
    
    Hexagon(){ init(); };
    Hexagon(const HexagonArgs& args):m_innerColor(args.innerColor), m_outerColor(args.outerColor), m_radius(args.radius){ init(); };
    ~Hexagon(){};
    
private:
    
    void init();
    glm::vec3 m_innerColor = Color::Black;
    glm::vec3 m_outerColor = Color::Black;
    float m_radius = 1.0f;
    
};

#endif /* Rectangle_hpp */
