#pragma once

#include <QtCore/QAbstractListModel>

class DataModel : public QAbstractListModel {
  Q_OBJECT
 public:
  enum Roles { DataRole = Qt::UserRole + 1 };
  explicit DataModel(QObject* parent = nullptr);

  QHash<int, QByteArray> roleNames() const override;
  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index, int role) const override;

  void insertData(const QVariant& data);

 private:
  QVector<QVariant> data_;
};
