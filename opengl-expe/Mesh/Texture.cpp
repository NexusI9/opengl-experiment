//
//  Texture.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 11/09/2024.
//


#include <SDL2/SDL_image.h>
#include <iostream>
#include "Texture.hpp"
#include <GL/glew.h>
#include "../Utility/Constant.h"


Texture::Texture(std::string& fullpath, unsigned int slot):m_path((const char*)fullpath.c_str()), m_slot(slot){}


void Texture::load(){
    
    //Load Texture array
    SDL_Surface* picture = IMG_Load(m_path);

    glGenTextures(1, &ID);
    
    if(m_slot > 31){
        m_slot = 0;
        throw std::runtime_error("Texture slot out of bound ("+std::to_string(m_slot)+")");
    }
    if(!picture){
        throw std::runtime_error("Texture could not be loaded");
    }
    
    const GLenum slot = textureSlot[m_slot];
    //Assign texture to slot
    glActiveTexture(slot);
    
    //Make texture active (bind)
    bind();

    //fillup texture buffer
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, picture->w, picture->h, 0, GL_RGB, GL_UNSIGNED_BYTE, picture->pixels);
    
    //Enable multisample
    //glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, MSAA_SAMPLING, GL_RGB, picture->w, picture->h, GL_TRUE);
    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, ID, 0);

    
    //Set Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    //Set Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    
    //unbind
    unbind();
    
}

void Texture::bind(){
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}
