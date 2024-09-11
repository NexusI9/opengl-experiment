//
//  Texture.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 11/09/2024.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <string>


class Texture{
    
public:
    
    Texture(const std::string& fullpath, const int width, const int height);
    void load();

private:
    const char* m_path;
    int m_width;
    int m_height;

};

#endif /* Texture_hpp */
