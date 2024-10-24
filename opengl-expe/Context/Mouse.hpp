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
        
        if(event.type == SDL_MOUSEMOTION){
            
            //update current position
            ScreenPosition tempPosition{0,0};
            SDL_GetGlobalMouseState(&tempPosition.x, &tempPosition.y);
            m_position = tempPosition.vec2();
            
            if(m_first){
                m_lastPosition = m_position;
                m_first = false;
            }
            
            
            //update offset
            m_offset = m_position - m_lastPosition;
            m_offset *= -1; //invert y
            
            //update last position
            m_lastPosition = m_position;
            
            m_offset *= m_sensitivity;
            
        }
        
        
    };
    
    static glm::vec2 getOffset(){ return m_offset; };
    static glm::vec2 getPosition(){ return m_position; };
    
private:
    static float m_sensitivity;
    static glm::vec2 m_lastPosition;
    static glm::vec2 m_position;
    static glm::vec2 m_offset;
    static bool m_first;
    
};


#endif /* Mouse_hpp */
