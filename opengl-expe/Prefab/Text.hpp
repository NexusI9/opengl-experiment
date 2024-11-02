//
//  Text.hpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 26/10/2024.
//

#ifndef Text_hpp
#define Text_hpp

#include <stdio.h>
#include <iostream>

#include <string>
#include <unordered_map>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "./PrefabBase.h"

#include "../Model/Rectangle.hpp"
#include "../Mesh/Mesh.hpp"
#include "../Mesh/MeshGroup.hpp"
#include "../Material/DefaultMaterial.hpp"
#include "../Material/Texture.hpp"

#include "../Utility/Constant.h"

struct Glyph{
    Texture      texture;
    glm::ivec2   size;
    glm::ivec2   bearing;
    FT_Pos       advance;
    MeshGroup*   mesh;
};

struct Font{
    FT_Face face;
    std::map<char, Glyph> glyphs;
};


class Text : public PrefabBase{
    
public:
    
    Text(std::string& text, int size, glm::vec3 color = Color::Grey);
    ~Text(){};

    void useFont(std::string& path);

    
private:
    
    static FT_Library m_ftLib;
    static std::unordered_map<std::string, Font> m_fontList;
    
    std::string& m_text;
    int m_size;
    glm::vec3 m_color;
    
    std::string m_typeface = std::string(ROOT_DIR + "Assets/Fonts/Arial.ttf");
    FT_Face m_currentFont;
    
    std::map<char, Glyph> loadCharacters();
    void generate();
    
    
};

#endif /* Text_hpp */
