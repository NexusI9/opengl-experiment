//
//  Grid.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 17/10/2024.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <stdio.h>

#include "../Prefab.h"

#include "../../Scene/GameObject.h"
#include "../../Model/Rectangle.hpp"
#include "../../Model/Points.hpp"
#include "../../Material/SolidMaterial.hpp"

struct Axis{
    std::vector<glm::vec3> points;
    glm::vec3 color;
};

class Grid : public Prefab{
    
public:
    
    Grid(float scale = 10.0f, int division = 20, float thickness = 32.0);
    ~Grid(){}
    
    
private:
    
    float m_scale;
    int m_division;
    float m_thickness;
    
    void genGrid();
    void genAxis(Axis& axis);
    
};

#endif /* Grid_hpp */
