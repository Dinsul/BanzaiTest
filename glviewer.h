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

    void initializeGL(); // Метод для инициализирования opengl
    void resizeGL(int nWidth, int newHeight); // Метод вызываемый после каждого изменения размера окна
    void paintGL(); // Метод для вывода изображения на экран
    void keyPressEvent(QKeyEvent *keyEvent); // Для перехвата нажатия клавиш на клавиатуре
    void keyReleaseEvent(QKeyEvent *keyEvent);
//    void mouseMoveEvent(QMouseEvent *event); // Метод реагирует на перемещение указателя, но по умолчанию setMouseTracking(false)
//    void mousePressEvent(QMouseEvent *event); // Реагирует на нажатие кнопок мыши
//    void mouseReleaseEvent(QMouseEvent *me); // Метод реагирует на "отжатие" кнопки мыши

protected slots:
    void update();

};

#endif // OPENGLWIDGET_VIEWER_H
