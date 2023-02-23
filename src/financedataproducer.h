#pragma once

#include <QtCore/QByteArray>
#include <QtCore/QTimer>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include "dataproducerbase.h"

class FinanceDataProducer : public DataProducerBase {
  Q_OBJECT
 public:
  explicit FinanceDataProducer(DataProducerType::DataType type, QObject* parent = nullptr);

  void produceData(QTcpSocket* connection) override;

 private:
  QByteArray parseFinanceData(const QByteArray& json) const;

 private:
  std::unique_ptr<QNetworkReply> reply_;
  QNetworkAccessManager network_manager_;
  QTimer timer_;
};
