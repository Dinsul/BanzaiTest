#include "outlinermodel.h"

#include <QDebug>

OutlinerModel::OutlinerModel(QVector<Figure*> *storage) :
    QAbstractTableModel(),
    _storage(storage)
{

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
