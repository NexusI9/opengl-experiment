//
//  Mesh.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 19/09/2024.
//

#include "Gltf.hpp"
#include "../Utility/Utility.hpp"
#include <iostream>
#include "../Utility/Debugger.hpp"
#include "../Utility/Constant.h"


Gltf::Gltf(const char* path) : BaseObject(Type::OBJECT), m_path(path){
    
    std::string file = Utility::importFile(path);
    m_json = nlohmann::json::parse(file);
    m_data = getData();
    
    traverseNode(0);
    
}

std::unordered_map<std::string, Texture*> Gltf::loadedTextures;

std::vector<unsigned char> Gltf::getData(){
    
    std::string bytesText;
    std::string uri = m_json["buffers"][0]["uri"]; //gltf .bin uri
    
    std::string fileStr = std::string(m_path);
    std::string dir = Utility::fileDir(fileStr);
    
    bytesText = Utility::importFile( (dir + uri).c_str() );
    std::vector<unsigned char> data(bytesText.begin(), bytesText.end());
    
    return data;
}

std::vector<float> Gltf::getFloats(nlohmann::json accessor){
    
    std::vector<float> floatVec;
    
    unsigned int count = accessor["count"];
    std::string type = accessor["type"]; //float, vec2, vec3, vec4
    
    unsigned int bufferViewIndex = accessor.value("bufferView", 1); //value method allows to set backup in case no key found
    unsigned int accByteOffset = accessor.value("byteOffset", 0);
    
    nlohmann::json bufferView = m_json["bufferViews"][bufferViewIndex];
    unsigned int byteOffset = bufferView["byteOffset"];
    
    unsigned int stride;
    
    if(type == "SCALAR") stride = 1;
    else if(type == "VEC2") stride = 2;
    else if(type == "VEC3") stride = 3;
    else if(type == "VEC4") stride = 4;
    else throw std::invalid_argument("GLTF accessor type is invalid (SCALAR, VEC2/3/4)");
    
    unsigned int dataStart = byteOffset + accByteOffset;
    unsigned int dataLength = count * stride;
    for(unsigned int i = dataStart; i < dataStart + dataLength * 4; i+=4){
        unsigned char bytes[] = { m_data[i+1], m_data[i+2], m_data[i+3],  m_data[i+4] };
        float floatValue;
        std::memcpy(&floatValue, bytes, sizeof(float)); //convert bytes to float;
        floatVec.push_back(floatValue);
    }
    
    return floatVec;
    
}


std::vector<GLuint> Gltf::getIndices(nlohmann::json accessor){
    
    std::vector<GLuint> indices;
    
    unsigned int count  = accessor["count"];
    unsigned int type = accessor["componentType"];
    
    unsigned int bufferViewIndex = accessor.value("bufferView",0);
    unsigned int accByteOffset = accessor.value("byteOffset", 0);
    
    nlohmann::json bufferView = m_json["bufferViews"][bufferViewIndex];
    unsigned int byteOffset = bufferView["byteOffset"];
    
    unsigned int dataStart = byteOffset + accByteOffset;
    
    if(type == 5125){ //Unsigned int
        for(unsigned int i = dataStart; i < byteOffset + accByteOffset + count * 4; i+=4 ){
            unsigned char bytes[] = { m_data[i], m_data[i+1], m_data[i+2], m_data[i+3] };
            unsigned int value;
            std::memcpy(&value, bytes, sizeof (unsigned int)); //convert bytes to float;
            indices.push_back((GLuint) value);
        }
    }
    
    else if(type == 5123){ //Unsigned short
        for(unsigned int i = dataStart; i < byteOffset + accByteOffset + count * 2; i+=2 ){
            unsigned char bytes[] = { m_data[i], m_data[i+1] };
            unsigned short value;
            std::memcpy(&value, bytes, sizeof (unsigned short)); //convert bytes to float;
            indices.push_back((GLuint) value);
        }
    }
    
    else if(type == 5122){ //short
        for(unsigned int i = dataStart; i < byteOffset + accByteOffset + count * 2; i+=2 ){
            unsigned char bytes[] = { m_data[i], m_data[i+1] };
            short value;
            std::memcpy(&value, bytes, sizeof (short)); //convert bytes to float;
            indices.push_back((GLuint) value);
        }
    }
    
    return indices;
}

std::vector<glm::vec2> Gltf::getFloatsVector2(std::vector<float> floatVec){
    
    std::vector<glm::vec2> vectors;
    for(int i = 0; i < floatVec.size(); i+=2){
        vectors.push_back(glm::vec2(floatVec[i], floatVec[i+1]));
    }
    
    return vectors;
}


std::vector<glm::vec3> Gltf::getFloatsVector3(std::vector<float> floatVec){
    
    std::vector<glm::vec3> vectors;
    for(int i = 0; i < floatVec.size(); i+=3){
        vectors.push_back(glm::vec3(floatVec[i], floatVec[i+1], floatVec[i+2]));
    }
     
    return vectors;
}

std::vector<glm::vec4> Gltf::getFloatsVector4(std::vector<float> floatVec){
    
    std::vector<glm::vec4> vectors;
    for(int i = 0; i < floatVec.size(); i+=4){
        vectors.push_back(glm::vec4(floatVec[i], floatVec[i+1], floatVec[i+2], floatVec[i+3]));
    }
    
    return vectors;
}

std::vector<Vertex> Gltf::assembleVertices(
                                           std::vector<glm::vec3>& positions,
                                           std::vector<glm::vec3>& normals,
                                           std::vector<glm::vec2>& texUVs){
    
    std::vector<Vertex> vertices;
    
    for(int i = 0; i < positions.size(); i++){
        vertices.push_back(Vertex{
            positions[i],
            normals[i],
            glm::vec3(1.0f),
            texUVs[i]
        });
    }
    
    return vertices;
    
}

void Gltf::traverseNode(unsigned int nodeIndex, glm::mat4 matrix){
    //Recursively pass on parent matrix to children and push Models into cache
    //By default: all initial object are centered at the origin, need to extract mesh individual matrix to get their real location
    
    nlohmann::json node = m_json["nodes"][nodeIndex];
    NodeMesh nodeMesh = {
        nullptr,
        glm::vec3(0.0f),
        glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f),
        glm::mat4(1.0f)
    };
    
    //Get Translation
    if(node.find("translation") != node.end()){
        float transValues[3];
        for(unsigned int i = 0; i < node["translation"].size(); i++){
            transValues[i] = node["translation"][i];
        }
        nodeMesh.translation = glm::make_vec3(transValues);
    }
    
    //Get Rotation
    if(node.find("quaternion") != node.end()){
        float rotValues[4] = {
            node["rotation"][3],
            node["rotation"][0],
            node["rotation"][1],
            node["rotation"][2]
        };
        
        nodeMesh.rotation = glm::make_quat(rotValues);
    }
    
    //Get Scale
    if(node.find("scale") != node.end()){
        float scaleValues[3];
        for(unsigned int i = 0; i < node["scale"].size(); i++){
            scaleValues[i] = node["scale"][i];
        }
        nodeMesh.translation = glm::make_vec3(scaleValues);
    }
    
    //Get Matrix
    if(node.find("matrix") != node.end()){
        float matrixValues[4*4];
        for(unsigned int i = 0; i < node["matrix"].size(); i++){
            matrixValues[i] = node["matrix"][i];
        }
        nodeMesh.matrix = glm::make_mat4(matrixValues);
    }
    
    //Setup next node matrix
    glm::mat4 translate(1.0f);
    glm::mat4 scale(1.0f);
    glm::mat4 rotation(1.0f);
    
    translate = glm::translate(translate, nodeMesh.translation);
    rotation = glm::mat4_cast(nodeMesh.rotation);
    scale = glm::scale(scale, nodeMesh.scale);
    
    glm::mat4 nextNodeMatrix = matrix * nodeMesh.matrix * translate * rotation * scale;
    
    //Finally load mesh if exists
    if(node.find("mesh") != node.end()){
        nodeMesh.mesh = loadMesh(node["mesh"]);
        nodeMesh.matrix = nextNodeMatrix;
    }
    
    //Iterate through children
    if(node.find("children") != node.end()){
        for(unsigned int i = 0; i < node["children"].size(); i++){
            traverseNode(node["children"][i], nextNodeMatrix);
        }
    }
    
}

Mesh* Gltf::loadMesh(unsigned int meshIndex){
    
    //Get accessor indices
    unsigned int posAccInd = m_json["meshes"][meshIndex]["primitives"][0]["attributes"]["POSITION"];
    unsigned int normAccInd = m_json["meshes"][meshIndex]["primitives"][0]["attributes"]["NORMAL"];
    unsigned int texAccInd = m_json["meshes"][meshIndex]["primitives"][0]["attributes"]["TEXCOORD_0"];
    unsigned int idAccInd = m_json["meshes"][meshIndex]["primitives"][0]["indices"];
    
    
    //Get vertices components via accessor
    std::vector<float> posVec = getFloats(m_json["accessors"][posAccInd]);
    std::vector<glm::vec3> positions = getFloatsVector3(posVec);
    
    std::vector<float> normalVec = getFloats(m_json["accessors"][normAccInd]);
    std::vector<glm::vec3> normals = getFloatsVector3(normalVec);
    
    std::vector<float> texVec = getFloats(m_json["accessors"][texAccInd]);
    std::vector<glm::vec2> texUvs = getFloatsVector2(texVec);
    
    //Combines vertex components
    std::vector<Vertex> vertices = assembleVertices(positions, normals, texUvs);
    std::vector<GLuint> indices = getIndices(m_json["accessors"][idAccInd]);
    std::vector<Texture> textures = loadTextures();
    
    //init mesh
    Mesh* mesh = new Mesh(vertices, indices, textures);
    
    //load shaders
    //Setup our meshes collection and assign shader etc...
    const std::string vertShaderPath = ROOT_DIR + "Shader/default.vert";
    const std::string fragShaderPath = ROOT_DIR + "Shader/default.frag";
    
    mesh->loadShader(vertShaderPath, fragShaderPath, "outColor");
    
    return mesh;
}




std::vector<Texture> Gltf::loadTextures(){
    
    std::vector<Texture> textures;
    
    std::string pathStr = (std::string) m_path;
    std::string dir = Utility::fileDir(pathStr);
    
    unsigned int slot = 0;
    for(int i = 0; i < m_json["images"].size(); i++){
        std::string texPath = m_json["images"][i]["uri"];
        //Check if texture doesn't already exists
        if(loadedTextures.find(texPath) == loadedTextures.end()){
            Debugger::verbose("Loading texture: " + texPath, TEXTURE);
            std::string texturePath = (dir+texPath).c_str();
            Texture* texture = new Texture(texturePath, slot++);
            textures.push_back(*texture);
            loadedTextures[texPath] = texture;
        }else{
            textures.push_back(*loadedTextures[texPath]);
        }
    }
    
    return textures;
    
}


void Gltf::draw(Camera& camera){
    
    for(NodeMesh& node : m_meshes){
        if(node.mesh) node.mesh->draw(camera, node.matrix, node.translation, node.rotation, node.scale);
        
    }
    
}
