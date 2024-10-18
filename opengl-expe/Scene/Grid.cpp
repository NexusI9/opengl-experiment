//
//  Grid.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 17/10/2024.
//

#include "Grid.hpp"
#include "../Model/Rectangle.hpp"
#include "../Utility/Color.h"
#include "../Utility/Constant.h"


MeshGroup* Grid::init(){
    
    Rectangle rectangle;
    MeshGroup* gridMesh = rectangle.getMesh();
    SolidMaterial gridMaterial(
                               Color::Green,
                               std::string(ROOT_DIR + "Material/Shader/grid.vert"),
                               std::string(ROOT_DIR + "Material/Shader/grid.frag")
                               );
    
    gridMesh->setMaterial(gridMaterial);
    
    return gridMesh;
}
