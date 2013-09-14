#include <QApplication>
#include "glmain.h"

int main(int argc,char *argv[]){
    QApplication app(argc,argv);
    GLMain window;
    //QGLWidget window;
    window.show();
    return app.exec();
}
