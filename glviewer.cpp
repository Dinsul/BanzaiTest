#include "glviewer.h"

#include <QtOpenGL>
#include <QTimer>

GLViewer::GLViewer(QVector<Figure *> *figures, QWidget *parent) :
    QGLWidget(parent),
    _scale(2),
    _figures(figures)
{
    setFormat(QGLFormat(QGL::SingleBuffer | QGL::ColorIndex));
//    glDepthFunc(GL_LEQUAL); // Буфер глубины

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    timer->start(200);
}

GLViewer::~GLViewer()
{
}

double GLViewer::scale() const
{
    return _scale;
}

void GLViewer::setScale(double scale)
{
    _scale = scale;
}

void GLViewer::initializeGL()
{
    qglClearColor(Qt::gray);

    glEnable(GL_LINE_SMOOTH);
    glDisable(GL_LINE_STIPPLE);
}

void GLViewer::resizeGL(int newWidth, int newHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)newWidth, (GLint)newHeight);
    _areaWidth  = newWidth;
    _areaHeight = newHeight;
}

void GLViewer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glMatrixMode(GL_PROJECTION); // устанавливаем матрицу
    glLoadIdentity(); // загружаем матрицу
    glOrtho(-_areaWidth / _scale, _areaWidth / _scale, -_areaHeight / _scale, _areaHeight / _scale, -10.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLineWidth(1.);
    glBegin(GL_LINES);
    glColor3b(25, 100, 50);

    glVertex2d(0., -_areaHeight / 2);
    glVertex2d(0.,  _areaHeight / 2);

    glVertex2d(-_areaWidth / 2, 0.);
    glVertex2d( _areaWidth / 2, 0.);
    glEnd();

    for (auto *figure : *_figures)
    {
        figure->draw();
    }

}

void GLViewer::keyPressEvent(QKeyEvent *keyEvent)
{
    int key = keyEvent->key();

    switch (key)
    {
    case Qt::Key_Plus:
        _scale += 0.1;
        break;
    case Qt::Key_Minus:
        _scale -= 0.1;
        break;
    case Qt::Key_Shift:
        for (auto *figure : *_figures)
        {
            figure->setChanged(true);
        }
        break;
    default:
        break;
    }

}

void GLViewer::keyReleaseEvent(QKeyEvent *keyEvent)
{
    int key = keyEvent->key();

    switch (key)
    {
    case Qt::Key_Shift:
        for (auto *figure : *_figures)
        {
            figure->setChanged(false);
        }
        break;
    default:
        break;
    }

}

void GLViewer::update()
{
    updateGL();
}
