//
//  Debugger.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 24/09/2024.
//

#include "Debugger.hpp"
#include "../Model/Points.hpp"
#include "../Prefab/Text.hpp"

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

void Debugger::printVertex(std::vector<Vertex>& vertex){
    for(int v = 0; v < vertex.size(); v++){
        glm::vec3 vert = vertex[v].position;
        std::cout << v << "\t\t" << vert.x << "\t" << vert.y << "\t" << vert.z << std::endl;
    }
}

void Debugger::printVertex(VertexList& vertex){
    for(int v = 0; v < vertex.size(); v++){
        glm::vec3 vert = vertex[v].vertex.position;
        std::cout << v << "\t\t" << vert.x << "\t" << vert.y << "\t" << vert.z << std::endl;
    }
}

void Debugger::printVertex(Vertex& vertex){
    std::cout << "Position:" << "\t\t" << vertex.position.x << "\t" << vertex.position.y << "\t" << vertex.position.z << std::endl;
    std::cout << "Normal:" << "\t\t\t" << vertex.normal.x << "\t" << vertex.normal.y << "\t" << vertex.normal.z << std::endl;
    std::cout << "Color:" << "\t\t\t" << vertex.color.x << "\t" << vertex.color.y << "\t" << vertex.color.z << std::endl;
    std::cout << "UV:" << "\t\t\t\t" << vertex.texUV.x << "\t" << vertex.texUV.y << "\n" << std::endl;
}


void Debugger::drawRay(glm::vec3 start, glm::vec3 end, Scene& scene, glm::vec3 color){
    
    std::vector<glm::vec3> ray{start, end};
    static Points line(ray);
    
    static Mesh* lineMesh = new Mesh({.name = "line", .model = line});
    lineMesh->setDrawMode(Mesh::DrawMode::WIREFRAME);
    scene.add(lineMesh);
}

void Debugger::drawPoints(std::vector<glm::vec3>& pts, Scene& scene, glm::vec3 color, bool label){
    
    //generate point mesh
    Points points(pts);
    Mesh* pointMesh = new Mesh({.name = "points", .model = points});
    pointMesh->setDrawMode(Mesh::DrawMode::POINTS);
    
    //generate point index label
    if(label){
        
        for( int i = 0; i < pts.size(); i++){
            glm::vec3 point = pts[i];
            std::string index = std::to_string(i);
            Text text(index, Color::Green);
            Mesh* textMesh = text.getMesh();
            
            textMesh->setPosition(point.x + 0.25f, point.y, point.z + 0.5f);
            textMesh->setScale(0.15f);
            pointMesh->addChildren(textMesh);
        }
        
    }


    scene.add(pointMesh);
}

void Debugger::drawVertex(std::vector<Vertex>& vert, Scene& scene, glm::vec3 color, bool label){
    std::vector<glm::vec3> tempPoints;
    for(auto& vertex : vert) tempPoints.push_back(vertex.position);
    drawPoints(tempPoints, scene, color, label);
}

void Debugger::drawVertex(VertexList& list, Scene& scene, glm::vec3 color, bool label){
    std::vector<glm::vec3> tempPoints;
    for(auto& point : list) tempPoints.push_back(point.vertex.position);
    drawPoints(tempPoints, scene, color, label);
}


void Debugger::drawMesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, Scene& scene, glm::vec3 color){
    
    //Not tested yet..
    /*std::vector<Texture> tex{};
    delete mesh;
    mesh = new Mesh(vertices, indices, tex);

    mesh->setDrawMode(Mesh::DrawMode::DEBUGGER);
    scene.add(mesh);*/
}


void Debugger::printMeshInfo(Mesh& meshgroup){
    
    std::string info;
    
    int childrenSize = (int) meshgroup.getChildren().size();
    info += "MESH INFO\n";
    info += "Children size:\t" + std::to_string(childrenSize) + "\n\n";
    
    int i = 0;
    for(auto& mesh : meshgroup.getChildren()) {
        info += "CHILD " + std::to_string(i) + ":\n";
        info += "Name:\t\t\t" + static_cast<Mesh*>(mesh)->getName();
        info += "Vertex size:\t" + std::to_string(static_cast<Mesh*>(mesh)->getVertices().size());
        info += "Elements size:\t" + std::to_string(static_cast<Mesh*>(mesh)->getIndices().size());
        info += "Textures size:\t" + std::to_string(static_cast<Mesh*>(mesh)->getTextures().size());
        info += "\n";
        i++;
    }
    
    print(info, Verbose::Flag::MESH);
}

void Debugger::filterVerboseFlag(Verbose::Flag flag){
    m_verboseFilter = flag;
}

void Debugger::printVector(std::vector<int>& vector){
    for(auto& item : vector) {
        std::cout << item << ", ";
    }
    std::cout << std::endl;
}
