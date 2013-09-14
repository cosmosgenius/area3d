#include <QApplication>
#include "openglwindow.h"

int main(int argc,char *argv[]){
    QApplication app(argc,argv);
    OpenGLWindow window;
    //QGLWidget window;
    window.show();
    window.resize(600,600);
    return app.exec();
}
