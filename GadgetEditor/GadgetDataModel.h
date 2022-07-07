#ifndef GADGETEDITOR_H
#define GADGETEDITOR_H

#include <QAbstractTableModel>

#include "GadgetEditor_global.h"

class GADGETEDITOR_EXPORT GadgetDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit GadgetDataModel(QObject* parent);

    template<typename T>
    void setGadget(T *gadget)
    {
        beginResetModel();
        mGadgetValue = gadget;
        mGadgetMetaData = T::staticMetaObject;
        endResetModel();
    }

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    void* mGadgetValue = nullptr;
    QMetaObject mGadgetMetaData;
};

#endif // GADGETEDITOR_H
