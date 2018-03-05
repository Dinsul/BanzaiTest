#include "square.h"


#include <QDebug>

Square::Square(QString name, int edgeSize, QPoint position, uint32_t color, float LineWidthChanged) :
    Figure(name, position, color),
    _edgeSize(edgeSize),
    _LineWidthChajnged(LineWidthChanged)
{
    applySize(edgeSize);

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

void Square::applySize(int edgeSize)
{
    _vertexes.append(QPoint(-edgeSize,  edgeSize));
    _vertexes.append(QPoint(-edgeSize, -edgeSize));
    _vertexes.append(QPoint( edgeSize, -edgeSize));
    _vertexes.append(QPoint( edgeSize,  edgeSize));
}

GLfloat Square::LineWidthChajnged() const
{
    return _LineWidthChajnged;
}
int Square::size() const
{
    return _edgeSize;
}

void Square::setSize(int edgeSize)
{
    _edgeSize = edgeSize;
    applySize(_edgeSize);
}


void Square::setLineWidthChajnged(const float LineWidthChajnged)
{
    _LineWidthChajnged = LineWidthChajnged;
}
