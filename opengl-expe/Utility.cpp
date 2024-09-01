//
//  Shader.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 01/09/2024.
//

#include "Utility.hpp"
#include <fstream>
#include <sstream>

std::string Utility::importShader(const char *shaderFile){
    
    std::ifstream file(shaderFile);
    if(!file) return std::string();
    
    file.ignore(std::numeric_limits<std::streamsize>::max());
    std::streamsize size = file.gcount();
    
    if(size > 0x10000) return std::string(); //64k bit check sanity for shader
    
    file.clear();
    file.seekg(0, std::ios_base::beg);
    
    std::stringstream sstr;
    sstr << file.rdbuf();
    file.close();
    
    return sstr.str();
}
