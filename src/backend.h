#pragma once

#include <QProperty>
#include <QtCore/QObject>
#include <QtCore/QProperty>
#include <QtCore/QTimer>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QTcpSocket>

#include "datamodel.h"
#include "dataproducerbase.h"

class BackEnd : public QObject {
  Q_OBJECT
  Q_PROPERTY(DataModel *model READ model CONSTANT)
  Q_PROPERTY(QVariant dataReading READ dataReading NOTIFY dataReadingChanged
                 BINDABLE boundDataReading)
  Q_PROPERTY(DataProducerType::DataType dataType READ dataType NOTIFY
                 dataTypeChanged BINDABLE boundDataType)

public:
  explicit BackEnd(DataProducerType::DataType type, const quint16 port,
                   const QString &host_address, QObject *parent = nullptr);

  QVariant dataReading() const { return data_reading_; }

  DataProducerType::DataType dataType() const { return data_type_; }

  QBindable<QVariant> boundDataReading() { return &data_reading_; }
  QBindable<DataProducerType::DataType> boundDataType() { return &data_type_; }

  DataModel *model();

  void connectToData();

signals:
  void dataReadingChanged();
  void dataTypeChanged();

private:
  void readData();
  void setReading(const QVariant &data) { data_reading_ = data; }
  void setDataType(const DataProducerType::DataType type) { data_type_ = type; }

  QTimer timer_;
  QDataStream in_stream_;
  QTcpSocket socket_;
  DataModel model_;

  quint16 port_{};
  QString host_address_{};

  Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(BackEnd, QVariant, data_reading_, 0,
                                       &BackEnd::dataReadingChanged);
  Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(BackEnd, DataProducerType::DataType,
                                       data_type_,
                                       DataProducerType::DataType::SpeedData,
                                       &BackEnd::dataTypeChanged);
};
