//
//  Point.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 16/10/2024.
//

#ifndef Points_hpp
#define Points_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <vector>

#include "../Mesh/MeshBase.h"
#include "../Mesh/Vertex.h"
#include "../Mesh/Mesh.hpp"
#include "../Material/Texture.hpp"
#include "./Model.h"


struct PointArg{
    glm::vec3 positions;
    std::string& label;
};

class Points : public Model{
    
public:

    Points(std::vector<glm::vec3>& points);
    ~Points(){};

};


#include <stdio.h>

#endif /* Point_hpp */
