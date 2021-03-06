#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glviewer.h"
#include "outlinermodel.h"
#include "dialognewfigure.h"
#include "myrandom.h"

#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QHBoxLayout *myLayout = new QHBoxLayout(ui->widget);
    myLayout->setSpacing(2);
    myLayout->setContentsMargins(5, 5, 5, 5);
    myLayout->setObjectName(QStringLiteral("layoutForViewer"));

    _viewer = new GLViewer( &_figures, ui->centralWidget);
    myLayout->addWidget(_viewer);
    _viewer->show();

    //Create random figures
    int counts = getRandomRange(1, 7);

    for (int i = 0; i < counts; ++i)
    {
        createRandomFigure();
    }

    OutlinerModel      *model    = new OutlinerModel(&_figures);
    QAbstractItemModel *oldModel = ui->tableView_outliner->model();

    connect(ui->tableView_outliner, SIGNAL(clicked(QModelIndex)), this, SLOT(elementWasClicked(QModelIndex)));
    connect(ui->tableView_outliner, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editElement(QModelIndex)));

    ui->tableView_outliner->setModel(model);
    ui->tableView_outliner->setSelectionMode(QAbstractItemView::MultiSelection);

    ui->tableView_outliner->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    if (oldModel)
    {
        delete oldModel;
    }
}

MainWindow::~MainWindow()
{
    for (auto *figure : _figures)
    {
        delete figure;
    }

    delete _viewer;
    delete ui;
}

void MainWindow::createRandomFigure()
{
    int type = getRandomRange(1, 3);
    int x    = getRandomRange(0, _viewer->width())  - _viewer->width()  / _viewer->scale();
    int y    = getRandomRange(0, _viewer->height()) - _viewer->height() / _viewer->scale();
    int size = getRandomRange(10, 20);

    switch (type)
    {
    case Figure::FtCircle:
        _figures.append(new Circle(QString("Figure%1").arg(_figures.count()), size, QPoint(x, y)));
        break;
    case Figure::FtSquare:
        _figures.append(new Square(QString("Figure%1").arg(_figures.count()), size, QPoint(x, y)));
        break;
    case Figure::FtTriangle:
        _figures.append(new Triangle(QString("Figure%1").arg(_figures.count()), size, QPoint(x, y)));
        break;
    default:
        qDebug() << "Что-то пошло не так =(";
        break;
    }
}

void MainWindow::elementWasClicked(QModelIndex index)
{
    QTableView* table = (QTableView*)sender();

    if (table->selectionModel()->isSelected(index))
    {
        _figures.at(index.row())->setChanged(true);
    }
    else
    {
        _figures.at(index.row())->setChanged(false);
    }
}

void MainWindow::editElement(QModelIndex index)
{
    ui->tableView_outliner->reset();

    DialogNewFigure dialog(&_figures, index.row());
    dialog.exec();

    ui->tableView_outliner->selectRow(index.row());
}

void MainWindow::on_toolButton_add_clicked()
{
    OutlinerModel *model = (OutlinerModel *)(ui->tableView_outliner->model());

    model->insertRow(0);
}

void MainWindow::on_toolButton_remove_clicked()
{
    QItemSelectionModel *selectionModel = ui->tableView_outliner->selectionModel();

    QModelIndexList indexes = selectionModel->selectedIndexes();

    if (indexes.isEmpty())
    {
        return;
    }

    for(auto index : indexes)
    {
        OutlinerModel *model = (OutlinerModel *)(ui->tableView_outliner->model());
        model->removeRow(index.row(), QModelIndex());
    }

    ui->tableView_outliner->reset();
}
