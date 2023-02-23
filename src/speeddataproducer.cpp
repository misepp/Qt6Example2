#include "speeddataproducer.h"

#include <math.h>

#include <QtCore/QByteArray>
#include <QtCore/QDataStream>
#include <QtNetwork/QTcpSocket>

SpeedDataProducer::SpeedDataProducer(DataProducerType::DataType type, QObject* parent)
    : DataProducerBase{type, parent} {
  timer_.setInterval(1000);
  timer_.setSingleShot(false);
}

void SpeedDataProducer::produceData(QTcpSocket* connection) {
  QObject::connect(&timer_, &QTimer::timeout, this, [connection, this]() {
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);

    QByteArray ba{calculateRandomSpeedValue().toLocal8Bit()};

    out << ba;
    connection->write(data);
  });
  timer_.start();
}

QString SpeedDataProducer::calculateRandomSpeedValue() const {
  auto radians = (0 + (std::rand() % 180)) / 180.0 * M_PI;
  return QString::number(static_cast<int>(abs(sin(radians) + sin(4 * radians) / 4 + 2 * sin(radians / 16)) / 3 * 180));
}
