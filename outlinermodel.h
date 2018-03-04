#ifndef OUTLINERMODEL_H
#define OUTLINERMODEL_H

#include <QAbstractTableModel>

#include "figures/figures.h"

class OutlinerModel : public QAbstractTableModel
{
public:
    OutlinerModel(QVector<Figure*> *storage);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    QVector<Figure*> *_storage;

};

#endif // OUTLINERMODEL_H
