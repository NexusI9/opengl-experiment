//
//  Clock.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 14/09/2024.
//

#include "Clock.hpp"



Clock::Clock(){
    m_startTime = std::chrono::high_resolution_clock::now();
}


std::chrono::steady_clock::time_point Clock::getStartTime(){
    return m_startTime;
}

std::chrono::steady_clock::time_point Clock::getCurrentTime(){
    return m_currentTime;
}

float Clock::getDelta(){
    m_currentTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::duration<float>>(m_currentTime - m_startTime).count();
}




