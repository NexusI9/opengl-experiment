//
//  Debugger.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 24/09/2024.
//

#ifndef Debugger_hpp
#define Debugger_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "../Mesh/Vertex.h"
#include "../Model/Rectangle.hpp"
#include "../Mesh/MeshGroup.hpp"
#include "../Scene/Scene.hpp"

struct Verbose{
    
    enum class Flag{
        NONE,
        TEXTURE,
        MESH,
        VERTEX,
        SHADER
    };
    
    int integer(Verbose::Flag flag){
        return static_cast<std::underlying_type<Verbose::Flag>::type>(flag);
    }
    
};


class Debugger{

public:
    
    static bool printVerbose;
    static Verbose::Flag verboseFlag;
    
    static void print(const std::string& value, Verbose::Flag flag = Verbose::Flag::NONE);
    static void printVec3(glm::vec3& vector);
    static void printVec2(glm::vec2& vector);
    
    static void drawRay(glm::vec3 start, glm::vec3 end, Scene& scene);
    static void drawPoint(glm::vec3 pt, Scene& scene);
    static void drawMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, Scene& scene);
    
private:
    
    static const char* m_verboseFlag[5];
    static MeshGroup* point(float scale = 0.3f);
};


#endif /* Debugger_hpp */
