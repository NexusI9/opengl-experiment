//
//  Circle.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 10/11/2024.
//

#include "Circle.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

Circle::Circle(const CircleArgs& args):
m_radius(args.radius),
m_points(args.points),
m_color(args.color){
    generate();
}


void Circle::generate(){
    
    for(int p = 0; p < m_points; p++){
        
        float index = p * 2.0f * M_PI / m_points;
        
        m_vertex.push_back({
            .position = glm::vec3(std::sin(index) * m_radius, std::cos(index) * m_radius, 1.0f),
            .normal = glm::vec3(1.0f),
            .color = m_color,
            .texUV = glm::vec2(0.5 + std::sin(index)/2, 0.5 + std::cos(index)/2)
        });
        
    }

    
}
