#include "dataserver.h"

#include <QtNetwork/QTcpSocket>

namespace {
constexpr auto kErrorMessage{"Unable to start the data server: "};
}

DataServer::DataServer(DataProducerBase* data_producer, const quint16 port, const QString& host_address,
                       QObject* parent)
    : QTcpServer{parent}
    , data_producer_(data_producer)
    , port_(port)
    , host_address_(host_address) {
}

DataServer::~DataServer() {
  delete data_producer_;
}

void DataServer::startDataWrite() {
  if (current_connection_ != nullptr) {
    return;
  }

  current_connection_ = nextPendingConnection();
  if (current_connection_ != nullptr) {
    connect(current_connection_, &QAbstractSocket::disconnected, current_connection_, &QObject::deleteLater);
    data_producer_->produceData(current_connection_);
  }
}

void DataServer::startServer() {
  if (!listen(QHostAddress{host_address_}, port_)) {
    emit errorMessage(kErrorMessage + errorString());
    close();
    return;
  }
  QObject::connect(this, &QTcpServer::newConnection, this, &DataServer::startDataWrite);
}
