#include "GL_Material.hpp"

void GL_Material::SetMat4(std::string varName, glm::mat4 mat) {
    GETGL
    int location = gl->glGetUniformLocation(shader.programShaderObject, varName.c_str()); 
    gl->glUniformMatrix4fv(location, 1, false, glm::value_ptr(mat));
}

void GL_Material::SetInt(std::string varName, int val){
    GETGL
    int location = gl->glGetUniformLocation(shader.programShaderObject, varName.c_str()); 
    gl->glUniform1i(location,val);
}


void GL_Material::Init() {
    std::ifstream t(vertShaderSrc);
    std::stringstream vertBuffer;
    vertBuffer << t.rdbuf();
    shader.vertSrc= vertBuffer.str();

    
    t = std::ifstream (fragShaderSrc);
    std::stringstream fragBuffer;
    fragBuffer << t.rdbuf();
    shader.fragSrc= fragBuffer.str();

    t.close();
    shader.Compile();  
}
