//
//  Grid.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 17/10/2024.
//

#ifndef Grid_hpp
#define Grid_hpp
#include "./GameObject.h"
#include "../Mesh/MeshGroup.hpp"

class Grid{
    
    Grid(){}
    ~Grid(){}
    
    MeshGroup* init();
    
};

#include <stdio.h>

#endif /* Grid_hpp */
