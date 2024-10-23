//
//  KeyboardHandler.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 21/10/2024.
//

#ifndef Keyboard_hpp
#define Keyboard_hpp

#include <stdio.h>
#include <unordered_map>
#include <SDL2/SDL.h>

class Keyboard{
    
public:
    static void listen(SDL_Event& event){
        
        const SDL_Keycode key = event.key.keysym.sym;
        if(event.type == SDL_KEYDOWN && key) m_keys[key] = true;
        else if(event.type == SDL_KEYUP && key) m_keys[key] = false;
         
    };
    
    static bool isPressed(SDL_Keycode key){
        return m_keys.find(key) != m_keys.end() ? m_keys[key] : false;
    }

    static bool isReleased(SDL_Keycode key){
        return m_keys.find(key) != m_keys.end() ? m_keys[key] : false;
    }
    
private:
        static std::unordered_map<SDL_Keycode, bool> m_keys;
    
};



#endif /* Keyboard_hpp */
