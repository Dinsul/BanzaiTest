#include "figure.h"


Figure::Figure(QString name, QPoint position, uint32_t color, float lineWidth) :
    _name(name),
    _changed(false),
    _position(position),
    _colorAlpha ((color & 0xFF000000) >> 24),
    _colorRed   ((color & 0x00FF0000) >> 16),
    _colorGreen ((color & 0x0000FF00) >> 8),
    _colorBlue  (color & 0x000000FF),
    _lineWidth(lineWidth),
    _type(FtCustom)
{
}

Figure::Figure(QString name, int x, int y, uint32_t color, float lineWidth) :
    Figure(name, QPoint(x, y), color, lineWidth)
{
}


Figure::~Figure()
{

}

Figure::FigureType Figure::type() const
{
    return _type;
}

void Figure::setColor(uint32_t argb)
{
    _colorAlpha = (argb & 0xFF000000) >> 24;
    _colorRed   = (argb & 0x00FF0000) >> 16;
    _colorGreen = (argb & 0x0000FF00) >> 8;
    _colorBlue  = argb & 0x000000FF;
}

void Figure::setColor(char alpha, char red, char green, char blue)
{
    _colorAlpha = alpha;
    _colorRed   = red;
    _colorGreen = green;
    _colorBlue  = blue;

}

bool Figure::changed() const
{
    return _changed;
}

float Figure::LineWidth() const
{
    return _lineWidth;
}

QString Figure::name() const
{
    return _name;
}

void Figure::setName(const QString &name)
{
    _name = name;
}

QPoint Figure::position() const
{
    return _position;
}

void Figure::setPosition(const QPoint &position)
{
    _position = position;
}

void Figure::setLineWidth(float LineWidth)
{
    _lineWidth = LineWidth;
}

void Figure::setChanged(bool changed)
{
    _changed = changed;
}

void Figure::draw()
{
    glPushMatrix();
    glTranslatef(_position.x(), _position.y(), 0);

    glLineWidth(_lineWidth);
    glBegin(GL_LINE_LOOP);

    glColor4b(_colorRed, _colorGreen, _colorBlue, _colorAlpha);

    for (auto vertex : _vertexes)
    {
        glVertex2i(vertex.x(), vertex.y());
    }

    glEnd();

    glPopMatrix();
}

