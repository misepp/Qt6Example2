#include "prducerfactory.h"
#include "financedataproducer.h"
#include "speeddataproducer.h"

PrducerFactory::PrducerFactory(QObject* parent)
    : QObject{parent} {
}

DataProducerBase* PrducerFactory::createProducer(const QString& type) {
  if (type == "speed") {
      return new SpeedDataProducer(DataProducerType::DataType::SpeedData);
  } else {
      return new FinanceDataProducer(DataProducerType::DataType::CoinData);
  }
}
