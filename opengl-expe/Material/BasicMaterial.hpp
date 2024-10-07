//
//  Material.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 02/10/2024.
//

#ifndef BasicMaterial_hpp
#define BasicMaterial_hpp

#include <stdio.h>

#include "./Material.hpp"
#include "./Texture.hpp"
#include <glm/glm.hpp>

class BasicMaterial : public Material{
    
public:
    
    BasicMaterial(VAO& vao, VBO& vbo, std::vector<Vertex>& vertices) : Material(vao, vbo, vertices){};
    ~BasicMaterial(){};
    
    void setDiffuseMap(Texture* map);
    void setNormalMap(Texture* map);
    void setAOMap(Texture* map);
    void setHeightMap(Texture* map);
    void setEmissiveColor(glm::vec3 color);
    
    void loadShader(const std::string &vertShader, const std::string &fragShader, const std::string &fragName) override;
    
private:
    
    Texture* diffuseMap;
    Texture* normalMap;
    Texture* aoMap;
    Texture* heightMap;
    
    glm::vec3 color;
    

};



#endif /* Material_hpp */
