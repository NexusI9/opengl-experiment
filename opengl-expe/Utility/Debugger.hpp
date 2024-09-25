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

enum VerboseFlag{
    TEXTURE,
    MESH,
    VERTEX,
    SHADER
};

class Debugger{

public:
    
    static bool printVerbose;
    static VerboseFlag verboseFlag;
    
    static void verbose(const std::string& value, VerboseFlag flag);
    
    
};


#endif /* Debugger_hpp */
