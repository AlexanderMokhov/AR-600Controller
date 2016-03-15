#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>
#include <GL/glu.h>

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

    float rotX, rotY, rotZ; //i want access these variable so public
    void resizeGL(int width, int height);
    short int col;

protected:
    void initializeGL();
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *event);


signals:

public slots:

private:



};

#endif // GLWIDGET_H
