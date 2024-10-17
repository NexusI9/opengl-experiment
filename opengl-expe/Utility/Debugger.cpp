//
//  Debugger.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 24/09/2024.
//

#include "Debugger.hpp"
#include "../Model/Points.hpp"

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

void Debugger::drawRay(glm::vec3 start, glm::vec3 end, Scene& scene, glm::vec3 color){
    
}

void Debugger::drawPoints(std::vector<glm::vec3>& pts, Scene& scene, glm::vec3 color){
    
    static Points points(pts);
    MeshGroup* pointMesh = points.getMesh();
    
    static SolidMaterial pointMat(color);
    pointMesh->setMaterial(pointMat);
    
    pointMesh->setDrawMode(MeshBase::DrawMode::POINTS);
    scene.add(pointMesh);
}

void Debugger::drawMesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, Scene& scene, glm::vec3 color){
    
}
