#ifndef SQUARE_H
#define SQUARE_H

#include "figure.h"

class Square : public Figure
{
public:
    Square(QString name, int size, QPoint position,
           uint32_t color = 0x64640000, float LineWidthChanged = 4.0);

    virtual void draw();

    void setLineWidthChajnged(const float LineWidthChajnged);
    void setSize(int size);

    GLfloat LineWidthChajnged() const;

    int  size() const;

private:
    void applySize(int size);
    void addVertex(){}
    void clearVertexes(){}

    int     _edgeSize;
    GLfloat _LineWidthChajnged;
};

#endif // SQUARE_H
