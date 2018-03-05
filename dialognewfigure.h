#ifndef DIALOGNEWFIGURE_H
#define DIALOGNEWFIGURE_H

#include <QDialog>

namespace Ui {
class DialogNewFigure;
}

class Figure;

class DialogNewFigure : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewFigure(QVector<Figure *> *storage, int index, QWidget *parent = 0);
    ~DialogNewFigure();

private slots:
    void on_comboBox_type_activated(int index);
    void on_buttonBox_accepted();

private:
    Ui::DialogNewFigure *ui;
    QVector<Figure *>   *_storage;
    Figure              *_figure;
    int                  _index;
};

#endif // DIALOGNEWFIGURE_H
