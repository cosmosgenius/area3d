#ifndef BASEGL_H
#define BASEGL_H

#include <QtGui>
#include <QOpenGLFunctions_3_1>

class basegl : public QWindow
{
    Q_OBJECT

public slots:
    void renderLater();
    void renderNow();

public:
    explicit basegl(QWindow *parent = 0);
    ~basegl();

    virtual void render(QPainter *painter);
    virtual void render();

    virtual void initialize();

    void setAnimation();

private:
    bool m_update_pending;
    bool m_animating;
    int max_fps;

    QOpenGLContext *m_context;
    QOpenGLPaintDevice *m_device;
    QOpenGLFunctions_3_1 *m_funcs;

protected:
    void exposeEvent(QExposeEvent *);
    void event(QEvent *);
};

#endif // BASEGL_H
