#include "circle.h"
#include <math.h>

#ifndef PI
#define PI 3.14159
#endif

Circle::Circle(QString name, double radius, QPoint position, uint32_t color, uint32_t colorChanged, int segments) :
    Figure(name, position, color),
    _colorAlphaChanged (colorChanged & 0xFF000000 >> 24),
    _colorRedChanged   (colorChanged & 0x00FF0000 >> 16),
    _colorGreenChanged (colorChanged & 0x0000FF00 >> 8),
    _colorBlueChanged  (colorChanged & 0x000000FF),
    _segments(segments)

{
    setRadius(radius);
    _type = FtCircle;
}

void Circle::setRadius(double radius)
{
    for (uint32_t i = 0; i < _segments; ++i)
    {
        // currentAngle in radians. 2 * PI full circle
        // full circle devision on segments count and multiple on current segmetn
        double currentAngle = 2 * PI / _segments * i;
        double x = sin(currentAngle) * radius;
        double y = cos(currentAngle) * radius;

        _vertexes.append(QPoint((int)x, (int)y));
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

uint32_t Circle::segments() const
{
    return _segments;
}

void Circle::setSegments(const uint32_t &segments)
{
    _segments = segments;
}
