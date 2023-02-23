#pragma once

#include <QtCore/QObject>
#include <QtNetwork/QTcpServer>

#include "dataproducerbase.h"
class QTcpSocket;

class DataServer : public QTcpServer {
  Q_OBJECT

 public:
  explicit DataServer(DataProducerBase* data_producer, quint16 port, const QString& host_address,
                      QObject* parent = nullptr);
  ~DataServer();

  void startServer();

 signals:
  void errorMessage(const QString& message);

 private:
  void startDataWrite();

  QTcpSocket* current_connection_{nullptr};
  DataProducerBase* data_producer_;
  quint16 port_{};
  QString host_address_{};
};
