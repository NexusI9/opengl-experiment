//
//  Texture.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 11/09/2024.
//


#include <SDL2/SDL_image.h>
#include <iostream>
#include "Texture.hpp"
#include "GL/glew.h"


Texture::Texture(const std::string& fullpath, const int width, const int height, const int slot):m_path((const char*)fullpath.c_str()), m_width(width), m_height(height), m_slot(slot){}


void Texture::load(){
    
    //Load Texture array
    SDL_Surface* picture = IMG_Load(m_path);

    glGenTextures(1, &m_id);
    
    if(m_slot > 31){
        std::cout << "Texture slot out of bound, reassigned to 0 (GL_TEXTURE0)\n";
        m_slot = 0;
    }
    const GLenum slot = textureSlot[m_slot];
    //Assign texture to slot
    glActiveTexture(slot);
    
    //Make texture active (bind)
    glBindTexture(GL_TEXTURE_2D, m_id);
    
    //fillup texture buffer
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, picture->pixels);
    
    //Set Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    //Set Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    
}
