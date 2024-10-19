//
//  Grid.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 17/10/2024.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <stdio.h>

#include "../Scene/GameObject.h"
#include "../Mesh/MeshGroup.hpp"
#include "../Model/Rectangle.hpp"
#include "../Material/SolidMaterial.hpp"

class Grid{
    
public:
    
    Grid(float scale = 10.0f, int division = 20, float thickness = 32.0) : m_scale(scale), m_division(division), m_thickness(thickness){}
    ~Grid(){
        delete m_rectangle;
        delete m_material;
    }
    
    MeshGroup* getMesh();
    
private:
    
    float m_scale;
    int m_division;
    float m_thickness;
    Rectangle* m_rectangle = nullptr;
    SolidMaterial* m_material = nullptr;
    
};

#endif /* Grid_hpp */
