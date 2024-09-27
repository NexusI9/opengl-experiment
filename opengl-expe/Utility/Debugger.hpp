//
//  Debugger.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 24/09/2024.
//

#ifndef Debugger_hpp
#define Debugger_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <string>
#include <glm/glm.hpp>

enum VerboseFlag{
    NONE,
    TEXTURE,
    MESH,
    VERTEX,
    SHADER
};

class Debugger{

public:
    
    static bool printVerbose;
    static VerboseFlag verboseFlag;
    
    static void print(const std::string& value, VerboseFlag flag = NONE);
    static void printVec3(glm::vec3& vector);
    static void printVec2(glm::vec2& vector);
    
private:
    static const char* m_verboseFlag[5];

    

    
};


#endif /* Debugger_hpp */
