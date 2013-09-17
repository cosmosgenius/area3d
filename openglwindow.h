#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QtGui>
#include <QOpenGLFunctions_3_1>

class OpenGLWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWindow(QWindow *parent = 0);
    ~OpenGLWindow();

protected:
    QOpenGLContext *m_context;
    void render();
    virtual void initialize();
    void exposeEvent(QExposeEvent *event);

private:
    int increment;
    QOpenGLFunctions_3_1 *m_funcs;
    GLuint VertexArrayID;
};

#endif // OPENGLWINDOW_H
