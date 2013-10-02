#include "openglwindow.h"
#include <QDebug>

OpenGLWindow::OpenGLWindow(QWindow *parent):Basegl(parent)
{
    //accesing opengl version
    m_funcs = getFunc();
    const GLubyte *ver = m_funcs->glGetString(GL_VERSION);
    qDebug() << (char*) ver;
    increment = 0;
}

OpenGLWindow::~OpenGLWindow()
{

}

void OpenGLWindow::render()
{

    static const GLfloat g_vertex_buffer_data[] = {
       -0.1f, -0.1f, 0.0f,
        0.1f, -0.1f, 0.0f,
        0.0f, 0.1f, 0.0f,
    };

    static const GLfloat g_vertex_buffer_data1[] = {
        -0.4f, -0.4f, 0.0f,
        0.4f, -0.4f, 0.0f,
        0.0f, 0.4f, 0.0f,
    };

    GLuint vertexbuffer;
    m_funcs->glClearColor(0.0f,0.0f,0.0f,0.0f);
    m_funcs->glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_funcs->glGenBuffers(1,&vertexbuffer);
    m_funcs->glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    if(increment < 50){
        m_funcs->glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data,GL_STATIC_DRAW);
    }else if(increment < 100){
        m_funcs->glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data1), g_vertex_buffer_data1,GL_STATIC_DRAW);
    }else{
        m_funcs->glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data1), g_vertex_buffer_data1,GL_STATIC_DRAW);
        increment = 0;
    }
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
    increment++;
    //qDebug() << "Render called";
}

void OpenGLWindow::resizeEvent(QResizeEvent *event){
    m_funcs->glViewport(0, 0, (GLsizei) event->size().width(), (GLsizei) event->size().height());
}
