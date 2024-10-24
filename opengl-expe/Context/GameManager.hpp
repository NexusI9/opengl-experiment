//
//  GameManager.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 24/10/2024.
//

#ifndef GameManager_hpp
#define GameManager_hpp

#include <stdio.h>


class GameManager{
    
public:
    
    enum class Mode{
        DEBUGGER,
        BUILD,
        PLAYER
    };
    
    static Mode mode;
    
private:
    
};

#endif /* GameManager_hpp */
