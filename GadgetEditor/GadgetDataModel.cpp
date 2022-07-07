#include "GadgetDataModel.h"
#include <QMetaProperty>

GadgetDataModel::GadgetDataModel(QObject* parent)
    : QAbstractTableModel{parent}
{
}

int GadgetDataModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() || !mGadgetValue ? 0 : mGadgetMetaData.propertyCount();
}

int GadgetDataModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() || !mGadgetValue ? 0 : 2;
}

QVariant GadgetDataModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        if (index.column() == 0) {
            return QString{mGadgetMetaData.property(index.row()).name()};
        } else {
            return mGadgetMetaData.property(index.row()).readOnGadget(mGadgetValue);
        }
    default:
        return {};
    }
}

bool GadgetDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        if (index.column() == 1) {
            if (mGadgetMetaData.property(index.row()).writeOnGadget(mGadgetValue, value)) {
                emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
                return true;
            }
        }
    }
    return false;
}

Qt::ItemFlags GadgetDataModel::flags(const QModelIndex &index) const
{
    constexpr auto BasicFlags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    if (index.column() == 0) {
        return BasicFlags;
    }
    return BasicFlags | Qt::ItemIsEditable;
}
