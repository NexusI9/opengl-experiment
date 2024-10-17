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

void Debugger ::printMesh(Mesh& mesh){
    auto& vertices = mesh.getVertices();
    
    for(int v = 0; v < vertices.size(); v++){
        Vertex vertex = vertices[v];
        std::cout << v << "\t\t" << vertex.position.x << "\t" << vertex.position.y << "\t" << vertex.position.z << std::endl;
    }
}


void Debugger::drawRay(glm::vec3 start, glm::vec3 end, Scene& scene, glm::vec3 color){
    
    std::vector<glm::vec3> ray{start, end};
    static Points line(ray);
    
    MeshGroup* lineMesh = line.getMesh();
    lineMesh->setDrawMode(MeshBase::DrawMode::WIREFRAME);
    scene.add(lineMesh);
}

void Debugger::drawPoints(std::vector<glm::vec3>& pts, Scene& scene, glm::vec3 color){
    
    static Points points(pts);
    MeshGroup* pointMesh = points.getMesh();
    
    pointMesh->setDrawMode(MeshBase::DrawMode::POINTS);
    scene.add(pointMesh);
}

Mesh* Debugger::mesh = nullptr;

void Debugger::drawMesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, Scene& scene, glm::vec3 color){
    
    //Not tested yet..
    std::vector<Texture> tex{};
    delete mesh;
    mesh = new Mesh(vertices, indices, tex);

    mesh->setDrawMode(MeshBase::DrawMode::DEBUGGER);
    scene.add(mesh);
}
