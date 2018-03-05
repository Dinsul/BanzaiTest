#include "circle.h"
#include <math.h>

#ifndef PI
#define PI 3.14159
#endif

Circle::Circle(QString name, int radius, QPoint position, uint32_t color, uint32_t colorChanged, int segments) :
    Figure(name, position, color),
    _radius(radius),
    _segments(segments),
    _colorAlphaChanged ((colorChanged & 0xFF000000) >> 24),
    _colorRedChanged   ((colorChanged & 0x00FF0000) >> 16),
    _colorGreenChanged ((colorChanged & 0x0000FF00) >> 8),
    _colorBlueChanged  (colorChanged & 0x000000FF)

{
    applySize(_radius);
    _type = FtCircle;
}

void Circle::applySize(int radius)
{
    for (int i = 0; i < _segments; ++i)
    {
        // currentAngle in radians. 2 * PI full circle
        // full circle devision on segments count and multiple on current segmetn
        double currentAngle = 2 * PI / _segments * i;
        int x = sin(currentAngle) * radius;
        int y = cos(currentAngle) * radius;

        _vertexes.append(QPoint(x, y));
    }
}

void Circle::draw()
{
    glPushMatrix();
    glTranslatef(_position.x(), _position.y(), 0);

    glLineWidth(_lineWidth);

    glBegin(GL_LINE_LOOP);

    if (_changed)
    {
        glColor4b(_colorRedChanged, _colorGreenChanged, _colorBlueChanged, _colorAlphaChanged);
    }
    else
    {
        glColor4b(_colorRed, _colorGreen, _colorBlue, _colorAlpha);
    }

    for (auto vertex : _vertexes)
    {
        glVertex2i(vertex.x(), vertex.y());
    }

    glEnd();

    glPopMatrix();
}

int Circle::segments() const
{
    return _segments;
}

int Circle::size() const
{
    return _radius;
}

void Circle::setSize(int radius)
{
    _radius = radius;
    applySize(_radius);
}


void Circle::setSegments(const uint32_t &segments)
{
    _segments = segments;
}
