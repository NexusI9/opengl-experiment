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
#include <GL/glew.h>


struct TexturePathArg{
    const std::string& path;
    const unsigned int slot = 0;
};

struct TextureBufferArg{
    const unsigned char* buffer;
    const unsigned int   width;
    const unsigned int   height;
    const unsigned int   slot = 0;
};


class Texture{
    
public:
    
    Texture(const TexturePathArg& args):
        m_path((const char*)args.path.c_str()),
        m_slot(args.slot){
            import();
        }
    
    Texture(const TextureBufferArg& args):
        m_buffer(args.buffer),
        m_slot(args.slot),
        m_width(args.width),
        m_height(args.height){
            generate((void*) m_buffer, m_width, m_height, m_slot);
        };
    
    void bind();
    void unbind();

private:
    
    GLenum textureSlot[32] = {
        GL_TEXTURE0,
        GL_TEXTURE1,
        GL_TEXTURE2,
        GL_TEXTURE3,
        GL_TEXTURE4,
        GL_TEXTURE5,
        GL_TEXTURE6,
        GL_TEXTURE7,
        GL_TEXTURE8,
        GL_TEXTURE9,
        GL_TEXTURE10,
        GL_TEXTURE12,
        GL_TEXTURE13,
        GL_TEXTURE14,
        GL_TEXTURE15,
        GL_TEXTURE16,
        GL_TEXTURE17,
        GL_TEXTURE18,
        GL_TEXTURE19,
        GL_TEXTURE20,
        GL_TEXTURE21,
        GL_TEXTURE22,
        GL_TEXTURE23,
        GL_TEXTURE24,
        GL_TEXTURE25,
        GL_TEXTURE26,
        GL_TEXTURE27,
        GL_TEXTURE28,
        GL_TEXTURE29,
        GL_TEXTURE30,
        GL_TEXTURE31
    };
    
    const char* m_path;
    
    const unsigned char* m_buffer;
    unsigned int m_width;
    unsigned int m_height;
    
    unsigned int m_slot;

    GLuint ID;
    
    void import();
    void generate(void* pixels, unsigned int width, unsigned int height, const unsigned int slot);
};

#endif /* Texture_hpp */
