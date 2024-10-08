//
//  Shader.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 01/09/2024.
//

#include "Utility.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

std::string importFile(const char *path){
    
    std::ifstream file(path);
    if(!file) {
        std::cout << "Couldn't find file " << path << std::endl;
        return std::string();
    }
    
    file.ignore(std::numeric_limits<std::streamsize>::max());
    /*std::streamsize size = file.gcount();
    if(size > 0x10000){
        std::cout << "File exceed 64bits" << std::endl;
        return std::string(); //64k bit check sanity for shader
    }*/
    
    file.clear();
    file.seekg(0, std::ios_base::beg);
    
    std::stringstream sstr;
    sstr << file.rdbuf();
    file.close();
    
    return sstr.str();
}


std::string fileDir(std::string& path){
    return path.substr(0, path.find_last_of("/") + 1);
}
