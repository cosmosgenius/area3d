#include "basegl.h"
#include <QtCore/QCoreApplication>

Basegl::Basegl(QWindow *parent)
    :QWindow(parent)
    ,m_update_pending(false)
    ,m_animating(false)
    ,m_context(0)
    ,m_funcs(0)
    ,m_device(0)
    ,max_fps(66)
{
    setSurfaceType(QWindow::OpenGLSurface);
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setMajorVersion(3);
    format.setMinorVersion(1);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
    create();

    m_context = new QOpenGLContext(this);
    m_context->create();
    m_context->setFormat(format);
    m_context->makeCurrent(this);
    m_funcs = m_context->versionFunctions<QOpenGLFunctions_3_1>();
    if(!m_funcs){
        throw "m_funcs initialize failed";;
    }
    m_funcs->initializeOpenGLFunctions();
    initialize();
}

Basegl::~Basegl(){
    delete m_device;
}

void Basegl::initialize(){

}

void Basegl::render(QPainter *painter){
    Q_UNUSED(painter);
}

void Basegl::render(){
    if (!m_device)
        m_device = new QOpenGLPaintDevice;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    m_device->setSize(size());

    QPainter painter(m_device);
    render(&painter);
}

void Basegl::setAnimation(bool animating){
    m_animating = animating;
    if(m_animating)
        renderLater();
}

void Basegl::renderNow(){
    if(!isExposed())
        return;

    m_context->makeCurrent(this);

    render();

    m_context->swapBuffers(this);

    if(m_animating)
        renderLater();
}

void Basegl::renderLater(){
    if (!m_update_pending) {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

bool Basegl::event(QEvent *event){
    switch (event->type()) {
    case QEvent::UpdateRequest:
        m_update_pending = false;
        renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
}

void Basegl::exposeEvent(QExposeEvent *event){
    Q_UNUSED(event);

    if(isExposed())
        renderLater();
}

int Basegl::getMax_fps(){
    return max_fps;
}

void Basegl::setMax_fps(int fps){
    if(fps > 0)
        max_fps = fps;
}

QOpenGLFunctions_3_1 *Basegl::getFunc(){
    return m_funcs;
}
