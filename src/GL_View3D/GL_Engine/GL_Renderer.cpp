#include "GL_Renderer.hpp"
#include "GL_Util.hpp"

void GL_Renderer::Render( GL_Scene &scene) {
    surface->makeCurrent();
    GETGL
    
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |  GL_STENCIL_BUFFER_BIT);    
    scene.Render();
    
    surface->doneCurrent();
}


void GL_Renderer::Init(QOpenGLWidget *surface){
    //TMP
    this->surface = surface;
    surface->makeCurrent();
    GETGL

    // Set up the rendering context, load shaders and other resources, etc.:
    gl->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    gl->glDisable(GL_CULL_FACE);
    gl->glEnable(GL_DEPTH_TEST);
    
    gl->glEnable(GL_MULTISAMPLE);
    
    surface->doneCurrent();    
}    

void GL_Renderer::Resize(int w, int h) {
}
