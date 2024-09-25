//
//  Debugger.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 24/09/2024.
//

#include "Debugger.hpp"

bool Debugger::printVerbose = true;
VerboseFlag Debugger::verboseFlag;

void Debugger::verbose(const std::string& value, VerboseFlag flag){
    if(printVerbose){
        if(flag && verboseFlag != flag){
                std::cout << "[" << flag << "]" << value << std::endl;
            
        }else{
            std::cout << value << std::endl;
        }
    }
}
