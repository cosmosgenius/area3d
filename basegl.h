#ifndef BASEGL_H
#define BASEGL_H

#include <QtGui>
#include <QOpenGLFunctions_3_1>

class basegl : public QWindow
{
    Q_OBJECT
public:
    explicit basegl(QWindow *parent = 0);

    virtual void render();
    virtual void initialize();

    void startAnimation();
    void stopAnimation();

private:
    bool m_animate;
};

#endif // BASEGL_H
