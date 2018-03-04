#ifndef CIRCLE_H
#define CIRCLE_H

#include "figure.h"

class Circle : public Figure
{
public:

    Circle(QString name, double radius, QPoint position,
           uint32_t color = 0x64640000, uint32_t colorChanged = 0x64000064,
           int segments = 128);

    void draw();

    void setRadius(double radius);
    void setSegments(const uint32_t &segments);

    uint32_t segments() const;

private:
    void addVertex(){}
    void clearVertexes(){}

    GLbyte      _colorAlphaChanged;
    GLbyte      _colorRedChanged;
    GLbyte      _colorGreenChanged;
    GLbyte      _colorBlueChanged;
    uint32_t    _segments;
};


#endif // CIRCLE_H
