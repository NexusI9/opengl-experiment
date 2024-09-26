//
//  Window.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 31/08/2024.
//

#include <stdio.h>
#include <iostream>
#include "Window.hpp"

Window::Window(int w, int h, const std::string& t)
: m_width(w), m_height(h), m_title(t){
 
}

void Window::init(){
    
    //Initialize SDL with SDLI_INIT_VIDEO bitfield (includes everything for opengl)
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0 ){
        std::cout << "Could not initialize SDL, Error: " << SDL_GetError() << std::endl;
    }
    
    //Forward compatibility for opengl 3.2
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    
    //Create window/ "stencil buffer"
    m_window = SDL_CreateWindow((char *) m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_OPENGL);
    
    if(NULL == m_window){
        std::cout << "Window not created, Error: " << SDL_GetError() << std::endl;
    }
    
    //Create OpenGL Context and link it to Window
    m_context = SDL_GL_CreateContext(m_window);
    
    //GLEW init
    glewExperimental = GL_TRUE;
    glewInit();
    
    //Clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int Window::draw(Scene& scene){
    
    m_isOpen = true;
    bool loop = true;
    
    //Main loop
    while(loop){
        //Add event listener
        if(SDL_PollEvent(&m_windowEvent)){
            
            switch (m_windowEvent.type) {
                case SDL_QUIT:
                    loop = false;
                    break;
                    
                default:
                    break;
            }
            
        }
        
        scene.draw();
        SDL_GL_SwapWindow(m_window);
        
        //refresh screen
        glClear(GL_COLOR_BUFFER_BIT);
        
    }
    
    m_isOpen = false;
    
    //Destroy Window and Context before quitting
    SDL_DestroyWindow(m_window);
    SDL_GL_DeleteContext(m_context);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}

Window::~Window(){}


