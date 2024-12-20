//
//  Mesh.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 19/09/2024.
//

#ifndef Gltf_hpp
#define Gltf_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>

#include "../Vendor/nlohmann/json.hpp"
#include "../Material/Texture.hpp"

#include "../Scene/Camera.hpp"
#include "../Scene/GameObject.h"

#include "Model.h"
#include "../Mesh/Vertex.h"
#include "../Mesh/Mesh.hpp"


struct NodeMesh{
    Mesh mesh;
    glm::vec3 translation;
    glm::quat rotation;
    glm::vec3 scale;
    glm::mat4 matrix;
};


class Gltf : public Model{
  
public:
    Gltf(const char* path);
    
    static std::unordered_map<std::string, Texture> loadedTextures;
    
private:
    const char* m_path;
    nlohmann::json m_json;
    
    std::vector<unsigned char> m_data;
    std::vector<unsigned char> getData();
    
    std::vector<float> getFloats(nlohmann::json accessor);
    std::vector<GLuint> getIndices(nlohmann::json accessor);
    std::vector<Texture> loadTextures();
    
    std::vector<Vertex> assembleVertices(
                                         std::vector<glm::vec3>& positions,
                                         std::vector<glm::vec3>& normals,
                                         std::vector<glm::vec2>& texUVs
                                         );

    std::vector<glm::vec2> getFloatsVector2(std::vector<float> floatVec);
    std::vector<glm::vec3> getFloatsVector3(std::vector<float> floatVec);
    std::vector<glm::vec4> getFloatsVector4(std::vector<float> floatVec);
    
    void traverseNode(unsigned int node, glm::mat4 matrix = glm::mat4(1.0f));
    
    Mesh loadMesh(unsigned int meshIndex);
    std::vector<NodeMesh> m_nodeMeshes;
    std::vector<Mesh> m_meshes;
    
};



#endif /* Mesh_hpp */
