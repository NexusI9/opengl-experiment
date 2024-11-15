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
#include "../Mesh/VertexList.hpp"
#include "../Model/Rectangle.hpp"
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
    
    ~Debugger(){}
    
    static bool printVerbose;
    static void filterVerboseFlag(Verbose::Flag flag);
    static Verbose::Flag verboseFlag;
    
    static void print(const std::string& value, Verbose::Flag flag = Verbose::Flag::NONE);
    static void printVec3(glm::vec3& vector);
    static void printVec2(glm::vec2& vector);
    static void printVertices(std::vector<glm::vec3>& vertices);

    static void printVertex(VertexList& vertex);
    static void printVertex(std::vector<Vertex>& vertex);
    static void printVertex(Vertex& vertex);
    
    static void printMeshGroupInfo(MeshGroup& meshgroup);
    
    static void drawRay(glm::vec3 start, glm::vec3 end, Scene& scene, glm::vec3 color = Color::Green);
    static void drawPoints(std::vector<glm::vec3>& pts, Scene& scene, glm::vec3 color = Color::Green, bool label = true);
    
    static void drawVertex(std::vector<Vertex>& vert, Scene& scene, glm::vec3 color = Color::Green, bool label = true);
    static void drawVertex(VertexList& vert, Scene& scene, glm::vec3 color = Color::Green, bool label = true);
    static void drawMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, Scene& scene, glm::vec3 color = Color::Green);
    

    
private:
    
    static Verbose::Flag m_verboseFilter;
    static const char* m_verboseFlag[5];
    
};


#endif /* Debugger_hpp */
