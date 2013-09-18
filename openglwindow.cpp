#include "openglwindow.h"
#include <QDebug>

OpenGLWindow::OpenGLWindow(QWindow *parent):Basegl(parent)
{
    //accesing opengl version
    m_funcs = getFunc();
    const GLubyte *ver = m_funcs->glGetString(GL_VERSION);
    qDebug() << (char*) ver;

}

OpenGLWindow::~OpenGLWindow()
{

}

void OpenGLWindow::render()
{
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };
    GLuint vertexbuffer;
    m_funcs->glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_funcs->glGenBuffers(1,&vertexbuffer);
    m_funcs->glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    m_funcs->glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data,GL_STATIC_DRAW);

    m_funcs->glEnableVertexAttribArray(0);
    m_funcs->glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    m_funcs->glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void*)0
                );
    m_funcs->glDrawArrays(GL_TRIANGLES, 0, 3);
    m_funcs->glDisableVertexAttribArray(0);
    //qDebug() << "Render called";
}
