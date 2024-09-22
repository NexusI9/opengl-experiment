//
//  Shader.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 01/09/2024.
//

#ifndef Utility_hpp
#define Utility_hpp

#include <stdio.h>
#include <string>


class Utility{
    
    
public:
    
    static std::string importFile(const char* shaderFile);
    static std::string fileDir(std::string& path);
    
};

#endif /* Shader_hpp */
