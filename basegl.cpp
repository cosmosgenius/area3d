#include "basegl.h"

basegl::basegl(QWindow *parent):QWindow(parent)
{
    m_animate = false;
}

void basegl::render(){

}

void basegl::startAnimation(){
    if(m_animate)
        return;
    m_animate = true;
    renderLater();
}

void basegl::stopAnimation(){
    m_animate = false;
}
