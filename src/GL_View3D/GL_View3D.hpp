#pragma once

#include "CommonIncludes.hpp"

#include "GL_Engine/GL_Renderer.hpp"

class GL_View3D : public QOpenGLWidget
{
public:
    GL_View3D(QWidget *parent);
    void SetImage(ImProc::image Image);

protected:
    QTimer* timer;
    void initializeGL() override; 
    void Refresh();    
    void resizeGL(int w, int h) ;
    void paintGL() override;

    std::string GetGLErr();
    
    ~GL_View3D() {
        makeCurrent();
        renderer.Destroy();
        scene.Destroy();
        doneCurrent();
    }

    GL_Renderer renderer;
    GL_Scene scene;
    GL_Mesh mesh;

    //Event Listeners
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void wheelEvent(QWheelEvent *e);

    void Destroy() {}

    GL_Mesh *quad;

};