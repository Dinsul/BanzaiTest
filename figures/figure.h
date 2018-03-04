#ifndef FIGURE_H
#define FIGURE_H

#include <QList>
#include <QPoint>
#include <QGLWidget>


///
/// \brief The Figure class
/// Bases class for all figures
///
class Figure
{
public:
    //Oops! OpenGL use range 0-100 for coding colors
    Figure(QString name, QPoint position, uint32_t color = 0x64640000, float lineWidth = 2);
    Figure(QString name, int x, int y, uint32_t color = 0x64640000, float lineWidth = 2);
    virtual ~Figure();

    enum FigureType{
        FtCustom = 0,
        FtCircle,
        FtTriangle,
        FtSquare
    };

    virtual void draw();


    FigureType type() const;

    void setColor(uint32_t argb);
    void setColor(char alpha, char red, char green, char blue);
    void addVertex(QPoint vertex);
    void clearVertexes(void);
    void setChanged(bool changed);
    void setLineWidth(const GLfloat LineWidth);
    void setPosition(const QPoint &position);
    void setName(const QString &name);

    bool changed() const;
    QPoint position() const;
    GLfloat LineWidth() const;
    QString name() const;

protected:
    QString         _name;
    bool            _changed;
    QPoint          _position;
    GLbyte          _colorAlpha;
    GLbyte          _colorRed;
    GLbyte          _colorGreen;
    GLbyte          _colorBlue;
    GLfloat         _lineWidth;
    FigureType      _type;
    QList<QPoint>   _vertexes;

};

#endif // FIGURE_H
