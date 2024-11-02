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
Verbose::Flag Debugger::m_verboseFilter = Verbose::Flag::NONE;

const char* Debugger::m_verboseFlag[5] = {
    "ALL",
    "TEXTURE",
    "MESH",
    "VERTEX",
    "SHADER"
};

void Debugger::print(const std::string& value, Verbose::Flag flag){

    if(printVerbose &&
       (m_verboseFilter == Verbose::Flag::NONE || m_verboseFilter == flag)){
        if(static_cast<int>(verboseFlag) != static_cast<int>(flag)){
                std::cout << "[" << m_verboseFlag[static_cast<int>(flag)] << "]\n" << value << "\n" << std::endl;
        }else{
            std::cout << value << "\n" << std::endl;
        }
    }
}

void Debugger::printVec3(glm::vec3& vector){
    std::cout << "x: " << vector.x << "\ty: " << vector.y << "\tz: " << vector.z << std::endl;
}

void Debugger::printVec2(glm::vec2& vector){
    std::cout << "x: " << vector.x << "\ty: " << vector.y << std::endl;
}

void Debugger::printVertices(std::vector<glm::vec3>& vertices){
    for(int v = 0; v < vertices.size(); v++){
        glm::vec3 vertex = vertices[v];
        std::cout << v << "\t\t" << vertex.x << "\t" << vertex.y << "\t" << vertex.z << std::endl;
    }
}


void Debugger::drawRay(glm::vec3 start, glm::vec3 end, Scene& scene, glm::vec3 color){
    
    std::vector<glm::vec3> ray{start, end};
    static Points line(ray);
    
    static MeshGroup* lineMesh = line.getMesh();
    lineMesh->setDrawMode(MeshBase::DrawMode::WIREFRAME);
    scene.add(lineMesh);
}

void Debugger::drawPoints(std::vector<glm::vec3>& pts, Scene& scene, glm::vec3 color){
    
    static Points points(pts);
    static MeshGroup* pointMesh = points.getMesh();
    
    pointMesh->setDrawMode(MeshBase::DrawMode::POINTS);
    scene.add(pointMesh);
}

void Debugger::drawMesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, Scene& scene, glm::vec3 color){
    
    //Not tested yet..
    /*std::vector<Texture> tex{};
    delete mesh;
    mesh = new Mesh(vertices, indices, tex);

    mesh->setDrawMode(MeshBase::DrawMode::DEBUGGER);
    scene.add(mesh);*/
}


void Debugger::printMeshGroupInfo(MeshGroup& meshgroup){
    
    std::string info;
    
    int childrenSize = (int) meshgroup.getMeshes().size();
    info += "MESHGROUP INFO\n";
    info += "Children size:\t" + std::to_string(childrenSize) + "\n\n";
    
    int i = 0;
    for(auto& mesh : meshgroup.getMeshes()) {
        info += "CHILD " + std::to_string(i) + ":\n";
        info += mesh.info() + "\n\n";
        i++;
    }
    
    print(info, Verbose::Flag::MESH);
}

void Debugger::filterVerboseFlag(Verbose::Flag flag){
    m_verboseFilter = flag;
}
