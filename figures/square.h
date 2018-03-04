#ifndef SQUARE_H
#define SQUARE_H

#include "figure.h"

class Square : public Figure
{
public:
    Square(QString name, int edgeSize, QPoint position,
           uint32_t color = 0x64640000, float LineWidthChanged = 4.0);

    virtual void draw();

    void setEdgeSize(int edgeSize);
    void setLineWidthChajnged(const float LineWidthChajnged);

    GLfloat LineWidthChajnged() const;

private:
    void addVertex(){}
    void clearVertexes(){}

    GLfloat _LineWidthChajnged;
};

#endif // SQUARE_H
