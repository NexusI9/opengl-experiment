//
//  Mesh.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 19/09/2024.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include <vector>
#include "../Vendor/nlohmann/json.hpp"
#include "Shader.hpp"
#include "../Scene/Camera.hpp"

class Mesh{
  
public:
    
    Mesh(const char* path);
    void draw(Shader& shader, Camera& camera);
    
private:
    
    const char* m_path;
    std::vector<unsigned char> m_data;
    nlohmann::json m_json;
     
    
};



#endif /* Mesh_hpp */
