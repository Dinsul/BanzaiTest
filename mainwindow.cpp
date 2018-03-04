#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glviewer.h"
#include "outlinermodel.h"

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
    for (int i = 0; i < (random() % 3 + 1); ++i)
    {
        createRandomFigure();
    }

    OutlinerModel      *model    = new OutlinerModel(&_figures);
    QAbstractItemModel *oldModel = ui->tableView_outliner->model();

    connect(ui->tableView_outliner, SIGNAL(clicked(QModelIndex)), this, SLOT(rowChanged(QModelIndex)));

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
    int type = random() % 3 + 1;
    int x    = random() % _viewer->width()  - _viewer->width()  / _viewer->scale();
    int y    = random() % _viewer->height() - _viewer->height() / _viewer->scale();
    int size = random() % 20 + 10;

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

void MainWindow::rowChanged(QModelIndex index)
{
    (void) index;

    QItemSelectionModel *selectionModel = ((QTableView*)sender())->selectionModel();

    QModelIndexList indexes = selectionModel->selectedIndexes();

    for(auto *figure : _figures)
    {
        figure->setChanged(false);
    }

    for(auto index : indexes)
    {
        Figure *chengedFigure = _figures.at(index.row());

        chengedFigure->setChanged(true);
    }
}

void MainWindow::on_toolButton_add_clicked()
{
    createRandomFigure();
}

void MainWindow::on_toolButton_remove_clicked()
{
    QItemSelectionModel *selectionModel = ui->tableView_outliner->selectionModel();

    QModelIndexList indexes = selectionModel->selectedIndexes();

    for(auto index : indexes)
    {
        Figure *chengedFigure = _figures.at(index.row());
        _figures.remove(index.row());

        delete chengedFigure;
    }
}
