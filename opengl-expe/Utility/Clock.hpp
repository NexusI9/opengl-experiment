//
//  Clock.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 14/09/2024.
//

#ifndef Clock_hpp
#define Clock_hpp

#include <stdio.h>
#include <chrono>

class Clock{
    
    
public:
    
    Clock();
    
    float getDelta();
    std::chrono::steady_clock::time_point getStartTime();
    std::chrono::steady_clock::time_point getCurrentTime();
    
private:
    
    std::chrono::steady_clock::time_point m_startTime;
    std::chrono::steady_clock::time_point m_currentTime;
    
    float timePointToFloat(std::chrono::steady_clock::time_point tp);
    
};

#endif /* Clock_hpp */
