#include "openglwindow.h"
#include <QDebug>

OpenGLWindow::OpenGLWindow(QWindow *parent):QWindow(parent)
{
    qDebug() << "start OpenGLWindow()";
    setSurfaceType(QSurface::OpenGLSurface);
    create();

    qDebug() << "creating m_context";

    //Creating opengl context
    m_context = new QOpenGLContext;
    m_context->create();
    m_context->makeCurrent(this);

    //accesing opengl version
    const GLubyte *ver = glGetString(GL_VERSION);
    qDebug() << (char*) ver;

    qDebug() << "end OpenGLWindow()";
}

OpenGLWindow::~OpenGLWindow()
{
    delete m_context;
}
