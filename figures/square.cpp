#include "square.h"

Square::Square(QString name, int edgeSize, QPoint position, uint32_t color, double lineWidthChanged) :
    Figure(name, position, color),
    _edgeSize(edgeSize),
    _lineWidthChanged(lineWidthChanged)
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
        glLineWidth(_lineWidthChanged);
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

double Square::lineWidthChanged() const
{
    return _lineWidthChanged;
}

int Square::size() const
{
    return _edgeSize;
}

void Square::setSize(int size)
{
    _edgeSize = size;
    applySize(_edgeSize);
}


void Square::setLineWidthChanged(double lineWidth)
{
    _lineWidthChanged = lineWidth;
}
