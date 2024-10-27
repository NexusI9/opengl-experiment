//
//  Window.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 31/08/2024.
//

#include <stdio.h>
#include <iostream>
#include "Window.hpp"
#include "../Utility/Constant.h"
#include "./Keyboard.hpp"
#include "./Mouse.hpp"
#include "./GameManager.hpp"

Window::Window(int w, int h, const std::string& t)
: m_width(w), m_height(h), m_title(t){
 
}

void Window::init(){
    
    //Initialize SDL with SDLI_INIT_VIDEO bitfield (includes everything for opengl)
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0 ){
        std::cout << "Could not initialize SDL, Error: " << SDL_GetError() << std::endl;
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, MSAA_SAMPLING);
    
    //Create window/ "stencil buffer"
    m_window = SDL_CreateWindow((char *) m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_OPENGL);
    
    if(NULL == m_window){
        std::cout << "Window not created, Error: " << SDL_GetError() << std::endl;
        return;
    }
    
    //Create OpenGL Context and link it to Window
    m_context = SDL_GL_CreateContext(m_window);
    //SDL_GL_MakeCurrent(m_window, m_context);
    
    //GLEW init
    glewExperimental = GL_TRUE;
    glewInit();
    
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    
    //Backface culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    //Alpha handling
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    
    //Point debug
    glEnable(GL_PROGRAM_POINT_SIZE);
    
    glViewport(0, 0, m_width, m_height);

    SDL_GL_SetSwapInterval(1);
    //Clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    if(GameManager::mode == GameManager::Mode::DEBUGGER)
    {
        SDL_ShowCursor(SDL_DISABLE);
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }
    
}

int Window::draw(Scene& scene){
    
    m_isOpen = true;
    bool isRunning = true;
    SDL_Event e;
    
    //Main loop
    while(isRunning){
        //Add event listener
        while(SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT: isRunning = false;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
                
                default:
                //listen keyboard inputs
                Keyboard::listen(e);
            }
        }
        
        //listen mouse inputs
        Mouse::listen(e);
        
        //Process scene input
        scene.onInput(e);
        
        
        //refresh screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //Process scene draw
        scene.onDraw();
        
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
             std::cerr << "OpenGL error: " << err << std::endl;
        }

        SDL_GL_SwapWindow(m_window);
    }
    
    m_isOpen = false;
    
    //Destroy Window and Context before quitting
    SDL_DestroyWindow(m_window);
    SDL_GL_DeleteContext(m_context);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}

Window::~Window(){}


