#include "openglwindow.h"
#include <QDebug>

OpenGLWindow::OpenGLWindow(QWindow *parent):QWindow(parent)
{
    qDebug() << "start OpenGLWindow()";
    setSurfaceType(QSurface::OpenGLSurface);
    create();

    qDebug() << "creating m_context";
    m_context = new QOpenGLContext;
    m_context->create();

    qDebug() << "end OpenGLWindow()";
}

OpenGLWindow::~OpenGLWindow()
{

}
