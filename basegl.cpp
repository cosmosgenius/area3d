#include "basegl.h"
#include <QtCore/QCoreApplication>

basegl::basegl(QWindow *parent)
    :QWindow(parent)
    ,m_update_pending(false)
    ,m_animating(false)
    ,m_context(0)
    ,m_funcs(0)
    ,max_fps(66)
{
    setSurfaceType(QWindow::OpenGLSurface);
    m_context = new QOpenGLContext(this);
    m_context->create();
    m_context->makeCurrent(this);

    if(needsInitialize){
        m_funcs = m_context->versionFunctions<QOpenGLFunctions_3_1>();
        if(!m_funcs){
            qDebug() << "m_funcs initialize failed";
            exit(1);
        }
        m_funcs->initializeOpenGLFunctions();
        initialize();
    }
}

void basegl::initialize(){

}

void basegl::render(QPainter *painter){
    Q_UNUSED(painter);
}

void basegl::render(){
    if (!m_device)
        m_device = new QOpenGLPaintDevice;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    m_device->setSize(size());

    QPainter painter(m_device);
    render(&painter);
}

void basegl::setAnimation(bool animating){
    m_animating = animating;
    if(m_animating)
        renderLater();
}

void basegl::renderNow(){
    if(!isExposed())
        return;

    bool needsInitialize = false;

    m_context->makeCurrent(this);



    render();

    m_context->swapBuffers(this);

    if(m_animating)
        renderLater();
}

void basegl::renderLater(){
    if (!m_update_pending) {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}
void basegl::event(QEvent *event){
    switch (event->type()) {
    case QEvent::UpdateRequest:
        m_update_pending = false;
        renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
}

void basegl::exposeEvent(QExposeEvent *event){
    Q_UNUSED(event);

    if(isExposed())
        renderLater();
}

void basegl::getMax_fps(){
    return max_fps;
}

void basegl::setMax_fps(int fps){
    if(fps > 0)
        max_fps = fps;
}
