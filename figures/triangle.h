#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figure.h"

class Triangle : public Figure
{
public:
    Triangle(QString name, int radiusOfCircumcircle, QPoint position,
             uint32_t color = 0x64640000, double scaleChanged = 1.2);

    void applySize(int radius);

    void draw();

    int  size() const;
    void setSize(int size);

private:
    void addVertex(){}
    void clearVertexes(){}

    double _radiusOfCircumcircle;
    double _scaleChanged;

};

#endif // TRIANGLE_H
