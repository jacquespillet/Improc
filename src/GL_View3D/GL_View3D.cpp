#include "GL_View3D.hpp"
#include "GL_Engine/GL_Util.hpp"

GL_View3D::GL_View3D(QWidget *parent) : QOpenGLWidget(parent) { 
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSwapInterval(1);
    format.setSamples(8);        
    setFormat(format); // must be called before the widget or its parent window gets shown

    
    setFocusPolicy(Qt::ClickFocus);
    setMouseTracking(true);

    timer = new QTimer(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

//GL Overriden functions
std::string GL_View3D::GetGLErr()
{
    GETGL
    std::string err = "";
    GLenum glError = gl->glGetError();
    if(glError == GL_INVALID_ENUM) err = "GL_INVALID_ENUM";
    else if(glError == GL_INVALID_VALUE) err = "GL_INVALID_VALUE";
    else if(glError == GL_INVALID_OPERATION) err = "GL_INVALID_OPERATION";
    else if(glError == GL_STACK_OVERFLOW) err = "GL_STACK_OVERFLOW";
    else if(glError == GL_STACK_UNDERFLOW) err = "GL_STACK_UNDERFLOW";
    else if(glError == GL_OUT_OF_MEMORY) err = "GL_OUT_OF_MEMORY";
    else if(glError == GL_INVALID_FRAMEBUFFER_OPERATION) err = "GL_INVALID_FRAMEBUFFER_OPERATION";
    else if(glError == GL_TABLE_TOO_LARGE) err = "GL_TABLE_TOO_LARGE";
    else err = "NO ERROR";
    return err;
} 

void GL_View3D::initializeGL() {
    quad = GetQuad();
    scene.Add(quad);
    
    renderer.Init(this);    

    connect(timer, &QTimer::timeout, [this]() {
        std::time_t result = std::time(nullptr);            
        clock_t currentTime = clock();
        makeCurrent();
        Refresh();
        doneCurrent();
    });
    timer->start(10);
}


void GL_View3D::Refresh() {
    repaint();
    update();
}

void GL_View3D::paintGL()
{
    renderer.Render(scene);
}


void GL_View3D::resizeGL(int w, int h) {
    renderer.Resize(w, h);
}


void GL_View3D::keyPressEvent(QKeyEvent *e) {}

void GL_View3D::keyReleaseEvent(QKeyEvent *e) {}

void GL_View3D::mousePressEvent(QMouseEvent *e) {}

void GL_View3D::mouseReleaseEvent(QMouseEvent *e) {}

void GL_View3D::mouseMoveEvent(QMouseEvent *e) {}

void GL_View3D::wheelEvent(QWheelEvent *e) {}

void GL_View3D::SetImage(ImProc::image Image){
    makeCurrent();
    TextureCreateInfo info;
    GL_Texture tex(Image, info);
    quad->material->SetTexture(tex, "mainTexture");
    doneCurrent();
}