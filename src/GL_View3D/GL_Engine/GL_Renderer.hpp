#pragma once

#include "CommonIncludes.hpp"
#include "GL_Scene.hpp"
#include "GL_Shader.hpp"
#include "GL_Mesh.hpp"



class GL_Renderer {
public: 
    void Render( GL_Scene &scene);
    void Init(QOpenGLWidget *surface);

    void Resize(int w, int h);

    void Destroy() {
    }
private:
    QOpenGLWidget *surface;
    GL_Mesh *renderQuad;
};    