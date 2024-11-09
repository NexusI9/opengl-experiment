//
//  Text.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 26/10/2024.
//

#include "Text.hpp"
#include <algorithm>
#include "../Utility/Debugger.hpp"


FT_Library Text::m_ftLib;
std::unordered_map<std::string, Font> Text::m_fontList;

Text::Text(std::string& text, glm::vec3 color) : m_text(text), m_color(color){
    
    if(FT_Init_FreeType(&m_ftLib)){
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }
    
    //Load default typeface
    useFont(m_typeface);
    
    //Then generate text
    generate();
}


void Text::useFont(std::string &path){
    
    m_typeface = path;
    
    //Load font if not loaded yet and not error loading it
    if(m_fontList.find(m_typeface) != m_fontList.end()){
        std::cout << "INFO::FREETYPE: Font already loaded" << std::endl;
        return;
    }
    else if(FT_New_Face(m_ftLib, m_typeface.c_str(), 0, &m_currentFont) ){
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }
    

    //Define pixel size for raster
    FT_Set_Pixel_Sizes(m_currentFont, 0, m_size);
    
    if(FT_Load_Char(m_currentFont, 'X', FT_LOAD_RENDER)){
        std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
        return;
    }
    
    GlyphMap glyphs = loadGlyphs();
    Texture atlas = genAtlas(glyphs);
    
    //Push new font to static map
    m_fontList[m_typeface] = {
        m_currentFont,
        glyphs,
        atlas
    };
    
}

GlyphMap Text::loadGlyphs(){
    /*
     Create Glyph object for each font characters and store along their
     position, recangle mesh, texture and material
     **/
    
    std::map<char, Glyph> map = {};
    
    //disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    for(unsigned char c = 0; c < 128; c++){
    
        if(FT_Load_Char(m_currentFont, c, FT_LOAD_RENDER)){
            std::cout << "ERROR::FREETYPE: Failed to load Character" << std::endl;
            continue;
        }
        
        unsigned int height = m_currentFont->glyph->bitmap.rows;
        unsigned int width = m_currentFont->glyph->bitmap.width;
        
        //set atlas dimension
        m_atlasWidth += width;
        m_atlasHeight = std::max(m_atlasHeight, static_cast<int>(height));
        
        //load glyph coordinates
        Glyph glyph{
            .size = glm::ivec2(width, height),
            .bearing = glm::ivec2(m_currentFont->glyph->bitmap_left, m_currentFont->glyph->bitmap_top),
            .advance = m_currentFont->glyph->advance.x >> 6,
            .buffer = new unsigned char[width * height]
        };
        
        std::memcpy(glyph.buffer, m_currentFont->glyph->bitmap.buffer, width * height);
        
        map.insert(std::pair<char, Glyph>(c, glyph));
        
    }
    
    FT_Done_Face(m_currentFont);
    FT_Done_FreeType(m_ftLib);
    
    return map;
}

Texture Text::genAtlas(GlyphMap &glyphs){

    /*
     Create atlas texture
     */
    
    Texture atlas = Texture({
        .buffer = nullptr,
        .width = m_atlasWidth,
        .height = m_atlasHeight,
        .format = GL_RED,
        .wrap = GL_CLAMP_TO_EDGE,
        .slot = 0
    });
    
    
    int offset = 0;
    for(auto& [c, glyph] : glyphs ){
            
        const int glyphWidth = static_cast<GLsizei>(glyph.advance);
        
        atlas.drawRegion({
                    .x = offset,
                    .y = 0,
                    .width = glyphWidth,
                    .height = glyph.size.y,
                    .format = GL_RED,
                    .buffer = glyph.buffer
                });
        
        offset += glyphWidth;
    }

   return atlas;
}

Texture Text::genLabel(std::string label, GlyphMap &glyphs){
    
    std::string::const_iterator c;
    GLsizei width = 0;
    GLsizei height = 0;
    GLsizei bearing = 0;
    
    //Precalculate label texture width and height
    for(c = label.begin(); c != label.end(); c++){
        Glyph glf = m_fontList[m_typeface].glyphs[*c];
        
        int margin = glf.size.y - glf.bearing.y;
        
        //Define global texture dimension
        width += static_cast<GLsizei>(glf.advance);
        height = std::max(height, glf.size.y + margin); //global height
        bearing = std::max(bearing, glf.size.y); //bearing height
    }
    
    Texture labelTexture = Texture({
        .buffer = nullptr,
        .width = width,
        .height = height,
        .format = GL_RGBA,
        .wrap = GL_CLAMP_TO_BORDER,
        .filter = GL_LINEAR,
        .slot = 0
    });
    
    //Place regions
    int offset = 0;
    for(c = label.begin(); c != label.end(); c++){

        Glyph glyph = m_fontList[m_typeface].glyphs[*c];
        
        const int glyphWidth = glyph.size.x;
        const int margin = std::max(1, std::abs(glyph.bearing.y - glyph.size.y));
        
        labelTexture.drawRegion({
                    .x = offset,
                    .y = (bearing - glyph.size.y) * margin,
                    .width = glyphWidth,
                    .height = glyph.size.y,
                    .format = GL_RED,
                    .buffer = glyph.buffer
                });
        
        
        offset += glyph.advance;
    }
    
    return labelTexture;
}

void Text::generate(){
    
    /*
     Generate Label texture and rectangle and assign the texture and material to it
     **/
    
    Texture labelTex = genLabel(m_text, m_fontList[m_typeface].glyphs);
    glm::vec2 texSize = labelTex.size();
    Rectangle rect;
    MeshGroup* labelMesh = rect.getMesh();
    
    SolidMaterial labelMaterial({
        .color = m_color,
        .fragmentShader = std::string(ROOT_DIR+"Material/Shader/text.frag")
    });
    
    labelMesh->addTexture(labelTex);
    labelMesh->setMaterial(labelMaterial);
    labelMesh->setScale(texSize.x / texSize.y, 1.0f, 1.0f); //scale to ratio
    
    m_mesh = labelMesh;
}

