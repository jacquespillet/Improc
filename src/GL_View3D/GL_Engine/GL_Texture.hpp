#pragma once

#include "CommonIncludes.hpp"

struct TextureCreateInfo {
    GLint wrapS = GL_MIRRORED_REPEAT;
    GLint wrapT = GL_MIRRORED_REPEAT;
    GLint minFilter = GL_NEAREST;
    GLint magFilter = GL_NEAREST;
    bool generateMipmaps=false;
};

class GL_Texture {
public:
    GL_Texture() : loaded(false){}
    
    GL_Texture(char *filename, TextureCreateInfo createInfo) {
        this->filename = filename;
        GETGL
        gl->glGenTextures(1, &glTex);
        gl->glBindTexture(GL_TEXTURE_2D, glTex);

        gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, createInfo.wrapS);
        gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, createInfo.wrapT);
        gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, createInfo.minFilter);
        gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, createInfo.magFilter);
    


        GLint texType = 0;
        if(Image.NumChannels == 4) {
            texType = GL_RGBA;
        } else if(Image.NumChannels == 3) {
            texType = GL_RGB;
        } else if(Image.NumChannels == 1) {
            texType = GL_RED;
        }

        std::cout << "Texture:Constructor: Num channels " << filename << "  " <<  Image.NumChannels << std::endl;
        if (Image.Size > 0)
        {
            gl->glTexImage2D(GL_TEXTURE_2D, 0, texType, (int)Image.Width, (int)Image.Height, 0, texType, GL_UNSIGNED_BYTE, Image.Data);
            if(createInfo.generateMipmaps) gl->glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Texture:Constructor: ERROR::Failed to load texture" << std::endl;
            return;
        } 
        
        gl->glBindTexture(GL_TEXTURE_2D, 0);
        loaded = true;        
    }
    
    GL_Texture(ImProc::image Image, TextureCreateInfo createInfo) {
        GETGL
        gl->glGenTextures(1, &glTex);
        gl->glBindTexture(GL_TEXTURE_2D, glTex);

        gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, createInfo.wrapS);
        gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, createInfo.wrapT);
        gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, createInfo.minFilter);
        gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, createInfo.magFilter);
    
        GLint texType = 0;
        if(Image.NumChannels == 4) {
            texType = GL_RGBA;
        } else if(Image.NumChannels == 3) {
            texType = GL_RGB;
        } else if(Image.NumChannels == 1) {
            texType = GL_RED;
        }

        std::cout << "Texture:Constructor: Num channels " << filename << "  " <<  Image.NumChannels << std::endl;
        if (Image.Size > 0)
        {
            gl->glTexImage2D(GL_TEXTURE_2D, 0, texType, (int)Image.Width, (int)Image.Height, 0, texType, GL_UNSIGNED_BYTE, Image.Data);
            if(createInfo.generateMipmaps) gl->glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Texture:Constructor: ERROR::Failed to load texture" << std::endl;
            return;
        } 
        
        gl->glBindTexture(GL_TEXTURE_2D, 0);
        loaded = true;        
    }

    GLuint glTex;
    bool loaded=false;
    std::string filename;
    ImProc::image Image;
};