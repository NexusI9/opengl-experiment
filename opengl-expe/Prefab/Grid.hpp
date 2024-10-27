//
//  Grid.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 17/10/2024.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <stdio.h>

#include "./PrefabBase.h"
#include "../Scene/GameObject.h"
#include "../Mesh/MeshGroup.hpp"
#include "../Model/Rectangle.hpp"
#include "../Model/Points.hpp"
#include "../Material/SolidMaterial.hpp"

struct Axis{
    std::vector<glm::vec3> Points;
    glm::vec3 Color;
};

class Grid : public PrefabBase{
    
public:
    
    Grid(float scale = 10.0f, int division = 20, float thickness = 32.0);
    
    ~Grid(){
        delete m_rectangle;
        delete m_gridMaterial;
        
        delete m_xAxis;
        delete m_xAxisMaterial;
        
        delete m_yAxis;
        delete m_yAxisMaterial;
    }
    
    
private:
    
    float m_scale;
    int m_division;
    float m_thickness;
    
    //Grid
    Rectangle* m_rectangle = nullptr;
    SolidMaterial* m_gridMaterial = nullptr;
    
    //X Axis
    Points* m_xAxis = nullptr;
    SolidMaterial* m_xAxisMaterial = nullptr;
    
    //Y Axis
    Points* m_yAxis = nullptr;
    SolidMaterial* m_yAxisMaterial = nullptr;
    
    void genGrid();
    void genAxis(Axis axis, Points* model, SolidMaterial* material);
    
};

#endif /* Grid_hpp */
