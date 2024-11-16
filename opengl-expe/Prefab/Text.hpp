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

#include "../Model/Model.h"

#include "../Model/Rectangle.hpp"
#include "../Mesh/Mesh.hpp"
#include "../Mesh/MeshGroup.hpp"
#include "../Material/DefaultMaterial.hpp"
#include "../Material/Texture.hpp"
#include "../Material/Uniform.h"

#include "../Utility/Constant.h"


struct Glyph{
    glm::ivec2      size;
    glm::ivec2      bearing;
    FT_Pos          advance;
    unsigned char*  buffer;
};


using GlyphMap = std::map<char, Glyph>;

struct Font{
    FT_Face face;
    GlyphMap glyphs;
    Texture atlas;
};

class Text : public Model{
    
public:
    
    Text(std::string& text, glm::vec3 color = Color::Grey);
    ~Text(){};

    void useFont(std::string& path);

    
private:
    
    static FT_Library m_ftLib;
    static std::unordered_map<std::string, Font> m_fontList;
    
    std::string& m_text;
    int m_size = 128;
    glm::vec3 m_color;
    
    std::string m_typeface = std::string(ROOT_DIR + "Assets/Fonts/Arial.ttf");
    FT_Face m_currentFont;
    
    GlyphMap loadGlyphs();
    
    Texture genAtlas(GlyphMap& glyphs);
    Texture genLabel(std::string label, GlyphMap& glyphs);
    GLsizei m_atlasWidth = 0;
    GLsizei m_atlasHeight = 0;
    
    
    void generate();
    
    
};

#endif /* Text_hpp */
