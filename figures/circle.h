#ifndef CIRCLE_H
#define CIRCLE_H

#include "figure.h"

class Circle : public Figure
{
public:

    Circle(QString name, int radius, QPoint position,
           uint32_t color = 0x64640000, uint32_t colorChanged = 0x64000064,
           int segments = 128);

    void draw();

    void setSegments(const uint32_t &segments);
    void setSize(int size);

    int segments() const;
    int  size() const;

private:
    void applySize(int size);
    void addVertex(){}
    void clearVertexes(){}

    int         _radius;
    int         _segments;
    GLbyte      _colorAlphaChanged;
    GLbyte      _colorRedChanged;
    GLbyte      _colorGreenChanged;
    GLbyte      _colorBlueChanged;
};


#endif // CIRCLE_H
