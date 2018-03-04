#include "square.h"


#include <QDebug>

Square::Square(QString name, int edgeSize, QPoint position, uint32_t color, float LineWidthChanged) :
    Figure(name, position, color),
    _LineWidthChajnged(LineWidthChanged)
{
    setEdgeSize(edgeSize);

    _type = FtSquare;
}

void Square::draw()
{
    glPushMatrix();
    glTranslatef(_position.x(), _position.y(), 0);

    if (_changed)
    {
        glLineWidth(_LineWidthChajnged);
    }
    else
    {
        glLineWidth(_lineWidth);
    }

    glBegin(GL_LINE_LOOP);

    glColor4b(_colorRed, _colorGreen, _colorBlue, _colorAlpha);

    for (auto vertex : _vertexes)
    {
        glVertex2i(vertex.x(), vertex.y());
    }

    glEnd();

    glPopMatrix();
}

void Square::setEdgeSize(int edgeSize)
{
    _vertexes.append(QPoint(0, 0));
    _vertexes.append(QPoint(0, edgeSize));
    _vertexes.append(QPoint(edgeSize, edgeSize));
    _vertexes.append(QPoint(edgeSize, 0));
}

GLfloat Square::LineWidthChajnged() const
{
    return _LineWidthChajnged;
}

void Square::setLineWidthChajnged(const float LineWidthChajnged)
{
    _LineWidthChajnged = LineWidthChajnged;
}
