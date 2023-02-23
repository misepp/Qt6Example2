#pragma once

#include <QtCore/QObject>
class QTcpSocket;

namespace DataProducerType {
Q_NAMESPACE
enum class DataType { SpeedData, CoinData };
Q_ENUM_NS(DataType)
}

class DataProducerBase : public QObject {
  Q_OBJECT
 public:
  explicit DataProducerBase(DataProducerType::DataType type, QObject* parent = nullptr);
  virtual ~DataProducerBase() = default;

  virtual void produceData(QTcpSocket* connection) = 0;

  DataProducerType::DataType dataType() { return data_type_; }

 protected:
  DataProducerType::DataType data_type_;
};
