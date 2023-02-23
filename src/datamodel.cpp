#include "datamodel.h"

DataModel::DataModel(QObject* parent)
    : QAbstractListModel(parent) {
}

QHash<int, QByteArray> DataModel::roleNames() const {
  return {{DataRole, "data"}};
}

int DataModel::rowCount(const QModelIndex& parent) const {
  return data_.size();
}

QVariant DataModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid() || index.row() >= data_.size()) {
    return {};
  }

  switch (role) {
    case DataRole: return data_[index.row()];
    default: return {};
  }
}

void DataModel::insertData(const QVariant& data) {
  if (data.isValid()) {
    beginInsertRows(QModelIndex(), data_.size(), data_.size());
    data_.push_back(data);
    endInsertRows();
  }
}
