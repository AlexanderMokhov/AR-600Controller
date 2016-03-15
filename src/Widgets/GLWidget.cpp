#include "GLWidget.h"

GLWidget::GLWidget(QWidget *parent):
    QGLWidget(parent)
{
    startTimer( 11 ); //64-65fps
    rotX = rotY = rotZ = 0.f;
    col = 0;
}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
    //initialization of OpenGL

    glClearColor(0.85f, 0.85f, 0.85f, 0.f);
    //resizeGL( 400 , 300 );

    glShadeModel( GL_SMOOTH );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_CULL_FACE );
    glEnable( GL_DEPTH_TEST );
}

void GLWidget::paintGL()
{
//    glClear(GL_COLOR_BUFFER_BIT);

//    glBegin(GL_TRIANGLES);
//    glColor3f(1, 1, 0);
//    glVertex3f(-0.2, -0.2 ,0);
//    glColor3f(0, 1, 0);
//    glVertex3f(0.2, -0.2 ,0);
//    glColor3f(0, 0, 1);
//    glVertex3f(0.0, 0.2 ,0);
//    glEnd();

//    glBegin(GL_TRIANGLES);
//    glColor3f(1, 1, 0);
//    glVertex3f(-0.2, -0.2 ,0);
//    glColor3f(0, 1, 0);
//    glVertex3f(0.2, -0.2 ,0);
//    glColor3f(0, 0, 1);
//    glVertex3f(0.0, 0.0 ,0.3);

//    glEnd();

    //draw scene here

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslated(0.0, 0.0, -1.0);

    glRotatef( rotX, 1, 0, 0 );
    glRotatef( rotY, 0, 1, 0 );
    glRotatef( rotZ, 0, 0, 1 );

      static const int coords[6][4][3] = {
        { { +1, -1, -1 }, { -1, -1, -1 }, { -1, +1, -1 }, { +1, +1, -1 } },
        { { +1, +1, -1 }, { -1, +1, -1 }, { -1, +1, +1 }, { +1, +1, +1 } },
        { { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 }, { +1, +1, +1 } },
        { { -1, -1, -1 }, { -1, -1, +1 }, { -1, +1, +1 }, { -1, +1, -1 } },
        { { +1, -1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { +1, -1, -1 } },
        { { -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 } }
    };

    for (int i = 0; i < 6; ++i) {
        glColor3ub( i*20+col, 100+i*10+col, i*42+col );
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; ++j) {
            glVertex3d(0.2 * coords[i][j][0], 0.2 * coords[i][j][1], 0.2 * coords[i][j][2]);
        }
        glEnd();
    }
    if(col > 200) col = 0;
    col++;

    rotX += 1.1;
    rotY += 1.4;
    rotZ += 1.6;
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{

}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void GLWidget::timerEvent(QTimerEvent *event)
{
    updateGL();
}

void GLWidget::resizeGL(int width, int height)
{
    //proces resize keep good aspect ratio for 3D scene

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    // glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 0.01f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

