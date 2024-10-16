//
//  Debugger.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 24/09/2024.
//

#include "Debugger.hpp"

bool Debugger::printVerbose = true;

Verbose::Flag Debugger::verboseFlag;

const char* Debugger::m_verboseFlag[5] = {
    "ALL",
    "TEXTURE",
    "MESH",
    "VERTEX",
    "SHADER"
};

void Debugger::print(const std::string& value, Verbose::Flag flag){

    if(printVerbose){
        if(static_cast<int>(verboseFlag) != static_cast<int>(flag)){
                std::cout << "[" << m_verboseFlag[static_cast<int>(flag)] << "] " << value << std::endl;
        }else{
            std::cout << value << std::endl;
        }
    }
}

void Debugger::printVec3(glm::vec3& vector){
    std::cout << "x: " << vector.x << "\ty: " << vector.y << "\tz: " << vector.z << std::endl;
}

void Debugger::printVec2(glm::vec2& vector){
    std::cout << "x: " << vector.x << "\ty: " << vector.y << std::endl;
}

void Debugger::drawRay(glm::vec3 start, glm::vec3 end, Scene& scene){
    
}

void Debugger::drawPoint(glm::vec3 pt, Scene& scene){
 
}

void Debugger::drawMesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, Scene& scene){
    
    MeshGroup* point = Debugger::point(3.0f);
    //std::cout << sizeof(point) << std::endl;
    scene.add(point);
    
}

MeshGroup* Debugger::point(float scale){
    
    //Generate plane
    static Rectangle rectangle;
    MeshGroup* meshes = rectangle.getMesh();
    
    //Apply to plane texture
    static SolidMaterial mat(Color::Green);
    meshes->setMaterial(mat);
    //meshes->setScale(scale, scale, scale);
    
    return meshes;
}
