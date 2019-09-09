#ifndef MYOPENGL_H
#define MYOPENGL_H
#include<QWidget>
#include<QOpenGLWidget>
#include<QOpenGLFunctions>
class MyOpenGL:public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MyOpenGL(QWidget *parent =nullptr);

protected:
    virtual void initializeGL()     Q_DECL_OVERRIDE;
    virtual void resizeGL(int w, int h)   Q_DECL_OVERRIDE;
    virtual void paintGL() Q_DECL_OVERRIDE;
signals:

public slots:

};

#endif // MYOPENGL_H
