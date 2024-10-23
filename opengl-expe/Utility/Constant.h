//
//  Constant.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 25/09/2024.
//

#ifndef Constant_h
#define Constant_h

#include <iostream>
#include <string>
#include <SDL2/SDL.h>


const std::string ROOT_DIR = (std::string) getenv("HOME") + "/Documents/XCode/opengl/opengl-expe/";

const int MSAA_SAMPLING = 4;

const SDL_Keycode INPUT_FORWARD = SDLK_z;
const SDL_Keycode INPUT_BACKWARD = SDLK_s;
const SDL_Keycode INPUT_LEFT = SDLK_q;
const SDL_Keycode INPUT_RIGHT = SDLK_d;

#endif /* Constant_h */
