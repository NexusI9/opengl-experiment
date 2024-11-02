//
//  Text.cpp
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 26/10/2024.
//

#include "Text.hpp"


FT_Library Text::m_ftLib;
std::unordered_map<std::string, Font> Text::m_fontList;

Text::Text(std::string& text, int size, glm::vec3 color) : m_text(text), m_size(size), m_color(color){
    
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
    
    //Push new font to static map
    m_fontList[m_typeface] = {
        m_currentFont,
        loadCharacters()
    };
    
}

std::map<char, Glyph> Text::loadCharacters(){
    /*
     Create Glyph object for each font characters and store along their
     position, recangle mesh, texture and material
     **/
    
    // disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    std::map<char, Glyph> map = {};
    
    for(unsigned char c = 0; c < 128; c++){
    

        if(FT_Load_Char(m_currentFont, c, FT_LOAD_RENDER)){
            std::cout << "ERROR::FREETYPE: Failed to load Character" << std::endl;
            continue;
        }
        
        unsigned int height = m_currentFont->glyph->bitmap.rows;
        unsigned int width = m_currentFont->glyph->bitmap.width;
        
        //Generate Texture
        Texture texture({
            .buffer = m_currentFont->glyph->bitmap.buffer,
            .width = width,
            .height = height,
            .slot = 0,
            .format = GL_RED,
            .wrap = GL_CLAMP_TO_EDGE
        });
        
        //Generate Plane Mesh and add texture and normalized scale
        Rectangle rectangle;
        
        MeshGroup* mesh = rectangle.getMesh();
        SolidMaterial material({
            .color = m_color,
            .fragmentShader = std::string(ROOT_DIR + "Material/Shader/text.frag")
        });
        
        mesh->setRotation(180.0f, 1.0f, 0.0f, 0.0f);
        mesh->addTexture(texture);
        mesh->setMaterial(material);
        mesh->setScale(width, height, 1.0f);
    
        Glyph glyph{
            texture,
            glm::ivec2(width, height),
            glm::ivec2(m_currentFont->glyph->bitmap_left, m_currentFont->glyph->bitmap_top),
            m_currentFont->glyph->advance.x,
            mesh
        };
        
        map.insert(std::pair<char, Glyph>(c, glyph));
        
    }
    
    FT_Done_Face(m_currentFont);
    FT_Done_FreeType(m_ftLib);
    
    return map;
}

void Text::generate(){
    
    /*
     Generate text string from the laded characters
     **/
    
    float cursor = 0.0f;
    std::string::const_iterator c;
    for(c = m_text.begin(); c != m_text.end(); c++){
        
        Glyph glf = m_fontList[m_typeface].glyphs[*c];
        //set plane mesh position based on character (glyph) property
        float xPos =  cursor + glf.bearing.x * m_size;
        float yPos = (glf.size.y - glf.bearing.y) * m_size;
        
        glf.mesh->setPosition(xPos, yPos, 0.0f);
        //push mesh to meshgroup
        m_mesh->addChildren(glf.mesh);
        
        //increment cursor
        // x >> 6  = x / 2^6 = x / 64, convert advance to full pixel (originaly 1/64th of a pixel)
        cursor += glf.advance >> 6 * m_size;
    }
    
}
