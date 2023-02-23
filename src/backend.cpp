#include "backend.h"

namespace {
constexpr auto kPollinterval{800};
}

BackEnd::BackEnd(DataProducerType::DataType type, const quint16 port, const QString& host_address, QObject* parent)
    : QObject{parent}
    , data_type_(type)
    , port_(port)
    , host_address_(host_address) {
  in_stream_.setDevice(&socket_);
  in_stream_.setVersion(QDataStream::Qt_6_2);
}

DataModel* BackEnd::model() {
  return &model_;
}

void BackEnd::connect() {
  connect(&socket_, &QIODevice::readyRead, this, &BackEnd::readData);
  connect(&socket_, &QAbstractSocket::errorOccurred, this,
          [](const QAbstractSocket::SocketError& err) { qDebug() << "ERROR " << err; });

  socket_.connectToHost(QHostAddress{host_address_}, port_);
}

void BackEnd::readData() {
  in_stream_.startTransaction();

  QByteArray next_reading;
  in_stream_ >> next_reading;

  if (!in_stream_.commitTransaction()) {
    return;
  }

  data_reading_ = next_reading.constData();
  model_.insertData(data_reading_);
}
