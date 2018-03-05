#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figure.h"

class Triangle : public Figure
{
public:
    Triangle(QString name, int radiusOfCircumcircle, QPoint position,
             uint32_t color = 0x7F640000, double scaleChanged = 1.2);


    void draw();
    void setSize(int size);
    int  size() const;

    void   setScaleChanged(double scaleChanged);
    double scaleChanged() const;

private:
    void applySize(int radius);
    int    _radiusOfCircumcircle;
    double _scaleChanged;
};

#endif // TRIANGLE_H
