//
//  Mouse.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 21/10/2024.
//

#ifndef Mouse_hpp
#define Mouse_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include "../Utility/Debugger.hpp"

struct ScreenPosition {
    int x;
    int y;

    ScreenPosition operator+(const ScreenPosition& a) const {
        return{x+a.x, y+a.y};
    }
    
    ScreenPosition operator-(const ScreenPosition& a) const {
        return{x-a.x, y-a.y};
    }
    
    ScreenPosition operator*(const ScreenPosition& a) const {
        return{x*a.x, y*a.y};
    }
    
    ScreenPosition operator*(const int& a) const {
        return{x*a, y*a};
    }
    
    glm::vec2 operator*(const float& a) const {
        return{x*a, y*a};
    }

    ScreenPosition operator/(const ScreenPosition& a) const {
        return{x/a.x, y/a.y};
    }
    
    glm::vec2 vec2() const {
        return glm::vec2{ (float) x, (float) y };
    }
    
};

class Mouse{
  
public:
    
    static void listen(SDL_Event& event){
            
            //update current position
            ScreenPosition tempPosition{0,0};
            SDL_GetRelativeMouseState(&tempPosition.x, &tempPosition.y);
            m_position = tempPosition.vec2();
            m_position *= -1; //invert
            
            Debugger::printVec2(m_position);
            std::cout << std::endl;
       
    };
    
    static glm::vec2 getPosition(){ return m_position; };
    
private:
    static glm::vec2 m_position;
    
};


#endif /* Mouse_hpp */
