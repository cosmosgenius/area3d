#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include "basegl.h"

class OpenGLWindow : public Basegl
{
    Q_OBJECT
public:
    explicit OpenGLWindow(QWindow *parent = 0);
    ~OpenGLWindow();

protected:
    QOpenGLContext *m_context;
    void render();

private:
    int increment;
    QOpenGLFunctions_3_1 *m_funcs;
    GLuint VertexArrayID;
    void resizeEvent(QResizeEvent *);
};

#endif // OPENGLWINDOW_H
