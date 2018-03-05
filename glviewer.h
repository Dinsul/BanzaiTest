#ifndef OPENGLWIDGET_VIEWER_H
#define OPENGLWIDGET_VIEWER_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>

#include "figures/figures.h"

class GLViewer : public QGLWidget
{
    Q_OBJECT

public:
    GLViewer( QVector<Figure*> *figures, QWidget *parent = 0);
    ~GLViewer();

    double scale() const;

    void setScale(double scale);

protected:

    double          _areaWidth;
    double          _areaHeight;
    double          _scale;

    QVector<Figure*>  *_figures;

    void initializeGL();
    void resizeGL(int nWidth, int newHeight);
    void paintGL();

protected slots:
    void update();

};

#endif // OPENGLWIDGET_VIEWER_H
