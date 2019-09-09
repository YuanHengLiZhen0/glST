#include"myopengl.h"
#include"frameRender.h"
MyOpenGL::MyOpenGL(QWidget *parent){

}
void MyOpenGL::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);

}

void MyOpenGL::paintGL(){
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   FrameRender render(QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_2_Core>());

   render.render();
}

void MyOpenGL::resizeGL(int w, int h){
     glViewport(0,0,w,h);
}
