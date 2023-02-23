#include "financedataproducer.h"

#include <QtCore/QDebug>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtNetwork/QNetworkRequest>

namespace {
constexpr auto kRequestUrl{"https://api.coindesk.com/v1/bpi/currentprice.json"};
constexpr auto kBpiKey{"bpi"};
constexpr auto kEurKey{"EUR"};
constexpr auto kValueKey{"rate_float"};
constexpr auto kNoParsedData{"No data was found"};
constexpr auto kReplyError{"REPLY ERROR: "};
constexpr auto kSocketError{"SOCKET ERROR: "};
}  // namespace

FinanceDataProducer::FinanceDataProducer(DataProducerType::DataType type, QObject* parent)
    : DataProducerBase{type, parent} {
  timer_.setInterval(1000);
  timer_.setSingleShot(false);
}

void FinanceDataProducer::produceData(QTcpSocket* connection) {
  QNetworkRequest request;
  request.setUrl(QUrl{kRequestUrl});

  connect(&timer_, &QTimer::timeout, this, [this, request, connection]() {
    reply_.reset(network_manager_.get(request));

    connect(reply_.get(), &QNetworkReply::errorOccurred, this,
            [this](QNetworkReply::NetworkError) { qDebug() << kReplyError << reply_->errorString(); });

    connect(connection, &QAbstractSocket::errorOccurred, this,
            [&, this]() {
        qDebug() << kSocketError << connection->errorString(); }
    );

    connect(reply_.get(), &QNetworkReply::finished, this, [this]() { reply_.reset(); });

    connect(reply_.get(), &QIODevice::readyRead, this, [&, this]() {
      QByteArray data;
      QDataStream out(&data, QIODevice::WriteOnly);
      out.setVersion(QDataStream::Qt_6_2);

      out << parseFinanceData(reply_->readAll());
      connection->write(data);
    });
  });

  timer_.start();
}

QByteArray FinanceDataProducer::parseFinanceData(const QByteArray& json) const {
  QJsonObject json_object = QJsonDocument::fromJson(json).object();
  if (!json_object.isEmpty()) {
    const auto& bpi_value = json_object[kBpiKey].toObject();
    if (!bpi_value.isEmpty()) {
      const auto& eur_value = bpi_value[kEurKey].toObject();
      if (!eur_value.isEmpty()) {
        const auto& btc_value = eur_value[kValueKey];
        if (btc_value.type() == QJsonValue::Double) {
          return QByteArray{QString::number(btc_value.toDouble()).toUtf8()};
        } else {
          return QByteArray{};
        }
      }
    }
  }
  return {kNoParsedData};
}
