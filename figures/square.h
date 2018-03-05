#ifndef SQUARE_H
#define SQUARE_H

#include "figure.h"

class Square : public Figure
{
public:
    Square(QString name, int size, QPoint position,
           uint32_t color = 0x64640000, double lineWidthChanged = 4.0);


    void draw();
    void setSize(int size);
    int  size() const;

    void  setLineWidthChanged(double lineWidth);
    double lineWidthChanged() const;

private:
    void applySize(int size);

    int    _edgeSize;
    double _lineWidthChanged;
};

#endif // SQUARE_H
