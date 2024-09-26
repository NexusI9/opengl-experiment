//
//  Debugger.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 24/09/2024.
//

#include "Debugger.hpp"

bool Debugger::printVerbose = true;

VerboseFlag Debugger::verboseFlag;

const char* Debugger::m_verboseFlag[5] = {
    "ALL",
    "TEXTURE",
    "MESH",
    "VERTEX",
    "SHADER"
};

void Debugger::verbose(const std::string& value, VerboseFlag flag){
    if(printVerbose){
        if(flag && verboseFlag != flag){
                std::cout << "[" << m_verboseFlag[flag] << "] " << value << std::endl;
            
        }else{
            std::cout << value << std::endl;
        }
    }
}
