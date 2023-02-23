#include "dataproducerbase.h"

DataProducerBase::DataProducerBase(DataProducerType::DataType type, QObject* parent)
    : QObject{parent}
    , data_type_(type) {
}
