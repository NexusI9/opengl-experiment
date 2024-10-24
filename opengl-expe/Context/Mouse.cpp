//
//  Mouse.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 21/10/2024.
//

#include "Mouse.hpp"

float Mouse::m_sensitivity = 0.1f;

glm::vec2 Mouse::m_position = {0.0f,0.0f};

glm::vec2 Mouse::m_lastPosition = {0.0f,0.0f};

glm::vec2 Mouse::m_offset = {0.0f,0.0f};

bool Mouse::m_first = true;
