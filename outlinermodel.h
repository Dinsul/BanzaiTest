#ifndef OUTLINERMODEL_H
#define OUTLINERMODEL_H

#include <QAbstractTableModel>

#include "figures/figures.h"

class OutlinerModel : public QAbstractTableModel
{
public:
    OutlinerModel(QVector<Figure*> *storage);

    void reload(void);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual bool removeRows(int row, int count, const QModelIndex &parent);
    virtual bool insertRows(int row, int count, const QModelIndex &parent);

private:

    QVector<Figure*> *_storage;

};

#endif // OUTLINERMODEL_H
