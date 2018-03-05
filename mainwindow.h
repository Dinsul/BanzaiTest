#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include "figures/figures.h"

class GLViewer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    GLViewer *_viewer;

    QVector<Figure*> _figures;

    void createRandomFigure();

private slots:
    void rowChanged(QModelIndex index);
    void editElement(QModelIndex index);
    void on_toolButton_add_clicked();
    void on_toolButton_remove_clicked();
};

#endif // MAINWINDOW_H
