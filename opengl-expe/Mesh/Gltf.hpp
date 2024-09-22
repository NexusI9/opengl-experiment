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

#include "Shader.hpp"
#include "../Vendor/nlohmann/json.hpp"
#include "../Scene/Camera.hpp"
#include "Texture.hpp"
#include "Vertex.h"


class Gltf{
  
public:
    Gltf(const char* path);
    
    void draw(Shader& shader, Camera& camera);
    
private:
    const char* m_path;
    nlohmann::json m_json;
    
    std::vector<unsigned char> m_data;
    std::vector<unsigned char> getData();
    
    static std::unordered_map<std::string, Texture> loadedTextures;
    
    std::vector<float> getFloats(nlohmann::json accessor);
    std::vector<int> getIndices(nlohmann::json accessor);
    std::vector<Texture> getTextures();
    
    std::vector<Vertex> assembleVertices(
                                         std::vector<glm::vec3>& positions,
                                         std::vector<glm::vec3>& normals,
                                         std::vector<glm::vec2>& texUVs
                                         );

    std::vector<glm::vec2> getFloatsVector2(std::vector<float> floatVec);
    std::vector<glm::vec3> getFloatsVector3(std::vector<float> floatVec);
    std::vector<glm::vec4> getFloatsVector4(std::vector<float> floatVec);
    
};



#endif /* Mesh_hpp */
