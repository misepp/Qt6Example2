#pragma once

#include <QtCore/QObject>
#include "dataproducerbase.h"

class PrducerFactory : public QObject
{
    Q_OBJECT
public:
    explicit PrducerFactory(QObject *parent = nullptr);

    static DataProducerBase* createProducer(const QString& type);
};
