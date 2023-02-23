#pragma once

#include <QtCore/QObject>
#include <QtCore/QTimer>

#include "dataproducerbase.h"

class SpeedDataProducer : public DataProducerBase {
  Q_OBJECT
 public:
  explicit SpeedDataProducer(DataProducerType::DataType type, QObject* parent = nullptr);

  void produceData(QTcpSocket* connection) override;

 private:
  QString calculateRandomSpeedValue() const;
  QTimer timer_;
};
