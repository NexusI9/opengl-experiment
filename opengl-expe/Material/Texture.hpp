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
#include <glm/glm.hpp>
#include "../Utility/Constant.h"


struct TexturePathArg{
    const std::string& path = std::string(ROOT_DIR+"Assets/Textures/default.png");
    const unsigned int slot = 0;
    const GLint        format = GL_RGB;
    const GLint        wrap = GL_REPEAT;
    const GLint        filter = GL_LINEAR;
};

struct TextureBufferArg{
    const void*          buffer = 0;
    const GLsizei        width = 1;
    const GLsizei        height = 1;
    const unsigned int   slot = 0;
    const GLint          format = GL_RGB;
    const GLint          wrap = GL_REPEAT;
    const GLint          filter = GL_LINEAR;
};

struct TextureRegion{
    GLint x = 0;
    GLint y = 0;
    GLsizei width = 1;
    GLsizei height = 1;
    GLint format = GL_RGB;
    const void* buffer = nullptr;
};

class Texture{
    
public:
    
    
    Texture(const TexturePathArg& args = {
        .path = std::string(ROOT_DIR+"Assets/Textures/default.png"),
        .slot = 0
    });
    Texture(const TextureBufferArg& args);
    ~Texture(){}
    
    void bind();
    void unbind();
    void drawRegion(const TextureRegion& args);
    glm::vec2 size(){ return glm::vec2(m_width, m_height); };
    
    std::string m_path;

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

    
    const void* m_buffer;
    unsigned int m_width;
    unsigned int m_height;
    
    unsigned int m_slot;
    GLint m_format;
    GLint m_wrap;
    GLint m_filter;

    GLuint ID = 0;
    
    void import();
    void generate(const void* pixels, unsigned int width, unsigned int height, const unsigned int slot);

};

#endif /* Texture_hpp */
