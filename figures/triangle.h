#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figure.h"

class Triangle : public Figure
{
public:
    Triangle(QString name, double radiusOfCircumcircle, QPoint position,
             uint32_t color = 0x64640000, double scaleChanged = 1.2);

    void setRadiusOfCircumcircle(double radius);

    void draw();

private:
    void addVertex(){}
    void clearVertexes(){}

    double _scaleChanged;

};

#endif // TRIANGLE_H
