#pragma once

#include "CommonIncludes.hpp"
#include "GL_Shader.hpp"
#include "GL_Texture.hpp"

class GL_Material {
public:
    GL_Material(){}

    GL_Material(std::string vertShaderSrc, std::string fragShaderSrc, bool shouldInit=false) : vertShaderSrc(vertShaderSrc), fragShaderSrc(fragShaderSrc) {
        if(shouldInit) Init();
    }
    
    ~GL_Material(){
        Destroy();
    }
    
    void Init();


    GL_Shader shader;
    void SetMat4(std::string varName, glm::mat4 mat);
    void SetInt(std::string varName, int val);

    void SetTexture(GL_Texture glTexture, std::string texName) {
        GETGL
        this->textureInformation =
        {
            glTexture,
            texName
        };
        BindTexture();
    }

    void BindTexture()
    {
        GETGL
        gl->glActiveTexture(GL_TEXTURE0);
        gl->glBindTexture(GL_TEXTURE_2D, textureInformation.texture.glTex);
        SetInt( textureInformation.name, 0);
    }

        
    void Destroy() { 
        GETGL
        gl->glUseProgram(0);
        gl->glDeleteProgram(shader.programShaderObject);
    }

    struct ShaderTexBinding {
        GL_Texture texture;
        std::string name;
    };
  
    ShaderTexBinding textureInformation;
    //0 : diffuse
    //1 : specular
    //2 : ambient
    //3 : emissive
    //4 : normals
    //5 : shininess
    //6 : opacity
    //7 : displacement
    //8 : ambientOcclusion


    
private:
    bool inited=false;
    std::string vertShaderSrc, fragShaderSrc;
};