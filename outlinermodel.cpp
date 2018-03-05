#include "outlinermodel.h"
#include "dialognewfigure.h"

#include <QDebug>

OutlinerModel::OutlinerModel(QVector<Figure*> *storage) :
    QAbstractTableModel(),
    _storage(storage)
{

}

void OutlinerModel::reload()
{
    emit dataChanged(QModelIndex(), QModelIndex());
    emit layoutChanged();
}

int OutlinerModel::rowCount(const QModelIndex &parent) const
{
    return _storage->count();
}

int OutlinerModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant OutlinerModel::data(const QModelIndex &index, int role) const
{
    if(role==Qt::BackgroundColorRole)
    {
        QColor color;
        if (index.row() %2 == 0)
            color.setRgb(0xF0,0xF0,0xF0);
        else
            color.setRgb(0xC0,0xC0,0xC0);

        return QVariant(color);
    }

    if (role == Qt::DisplayRole)
    {
        Figure *currentFigure = _storage->at(index.row());

        return QVariant(currentFigure->name());
    }

    else if (role == Qt::EditRole)
    {
        Figure *currentFigure = _storage->at(index.row());

        return QVariant(currentFigure->name());
    }

    return QVariant();
}

bool OutlinerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (value.isNull())
    {
        return false;
    }

    if (role == Qt::EditRole)
    {
        Figure *currentFigure = _storage->at(index.row());

        currentFigure->setName(value.toString());
    }

    emit dataChanged(index, index);
    emit layoutChanged();

    return true;
}

bool OutlinerModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (_storage->isEmpty() || row < 0 || row >= _storage->count())
    {
        return false;
    }

    Figure *chengedFigure = _storage->at(row);
    _storage->remove(row);

    delete chengedFigure;

    emit dataChanged(parent, parent);
    emit layoutChanged();

    return true;
}

bool OutlinerModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Figure *newFigure;

    DialogNewFigure dialog(&newFigure);
    dialog.exec();

    if (newFigure)
    {
        _storage->append(newFigure);
    }

    emit dataChanged(parent, parent);
    emit layoutChanged();

    return true;
}
