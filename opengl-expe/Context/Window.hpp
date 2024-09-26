//
//  Window.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 31/08/2024.
//

#ifndef Window_hpp
#define Window_hpp

#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <string>

#include "../Scene/Scene.hpp"


class Window{
    
public:
    
    Window(int w, int h, const std::string& title); //Constructor
    ~Window(); //Destructor
    
    void init();
    int draw(Scene& scene);
    bool m_isOpen;

    
private:

    int m_width;
    int m_height;
    const std::string& m_title;
    
    SDL_Event m_windowEvent;
    SDL_Window* m_window;
    SDL_GLContext m_context;
};


#endif /* Window */
