#include "openglwindow.h"
#include <QDebug>

OpenGLWindow::OpenGLWindow(QWindow *parent):QWindow(parent)
{
    qDebug() << "start OpenGLWindow()";
    setSurfaceType(QWindow::OpenGLSurface);
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setMajorVersion(3);
    format.setMinorVersion(1);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
    create();

    qDebug() << "creating m_context";

    //Creating opengl context
    m_context = new QOpenGLContext;
    m_context->setFormat(format);
    m_context->create();
    m_context->makeCurrent(this);

    //accesing opengl version
    const GLubyte *ver = glGetString(GL_VERSION);
    qDebug() << (char*) ver;

    //Obtain a function Object and resolve all entry points
    m_funcs = m_context->versionFunctions<QOpenGLFunctions_3_1>();
    if(!m_funcs){
        qDebug() << "m_funcs initialize failed";
        exit(1);
    }
    m_funcs->initializeOpenGLFunctions();

    increment = 0;
    initialize();
    qDebug() << "end OpenGLWindow()";
}

OpenGLWindow::~OpenGLWindow()
{
    delete m_context;
}

void OpenGLWindow::initialize(){
    qDebug() << "initialize called";
    m_funcs->glGenVertexArrays(1,&VertexArrayID);
    m_funcs->glBindVertexArray(VertexArrayID);
}

void OpenGLWindow::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event)
    qDebug() << increment++;
    if(isExposed())
        render();
}

void OpenGLWindow::render()
{
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };
    m_context->makeCurrent(this);
    m_context->swapBuffers(this);
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
    qDebug() << "Render called";
}
