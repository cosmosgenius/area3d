#include <QApplication>
#include "openglwindow.h"
#include <QDebug>

int main(int argc,char *argv[]){
    QApplication app(argc,argv);
    OpenGLWindow window;

    window.resize(600,600);
    window.show();

    return app.exec();
}
