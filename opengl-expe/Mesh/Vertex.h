//
//  Vertex.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 21/09/2024.
//

#ifndef Vertex_h
#define Vertex_h
#include <GL/glew.h>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texUV;
};

#endif /* Vertex_h */
