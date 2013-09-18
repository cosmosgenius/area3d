#include <QApplication>
#include "openglwindow.h"
#include <QDebug>

int main(int argc,char *argv[]){
    QApplication app(argc,argv);
    OpenGLWindow window;

    window.resize(400,400);
    window.show();
    window.setAnimation(true);
    return app.exec();
}
