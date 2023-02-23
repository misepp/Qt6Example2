#include <QtCore/QCommandLineParser>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlProperty>
#include <QtQml/QQmlContext>

#include "backend.h"
#include "dataproducerbase.h"
#include "dataserver.h"
#include "financedataproducer.h"
#include "prducerfactory.h"
#include "speeddataproducer.h"

int main(int argc, char* argv[]) {
  Q_INIT_RESOURCE(qml);
  Q_INIT_RESOURCE(assets);
  QGuiApplication app(argc, argv);

  QCommandLineParser parser;
  parser.addHelpOption();
  parser.addOption({"host_address", "Dataserver address to listen", "host_address", "127.0.0.1"});
  parser.addOption({"host_port", "Dataserver port", "host_address", "1234"});
  parser.addOption({"data_type", "Data type to fetch and display, speed OR finance", "data_type", "speed"});
  parser.process(app);

  QQmlApplicationEngine engine;

  const auto port = static_cast<quint16>(parser.value("host_port").toInt());
  const auto& address = parser.value("host_address");

  DataProducerBase* producer = PrducerFactory::createProducer(parser.value("data_type"));
  DataServer server{producer, port, address};
  BackEnd back_end{producer->dataType(), port, address};

  qmlRegisterSingletonInstance<BackEnd>("Example.Backend", 1, 0, "BackEnd", &back_end);
  qmlRegisterUncreatableMetaObject(DataProducerType::staticMetaObject, "Example.Constants", 1, 0, "Constants",
                                   "Should only be used for enums");


  const QUrl url(u"qrc:/main.qml"_qs);
  QObject::connect(
    &engine, &QQmlApplicationEngine::objectCreated, &app,
    [url](QObject* obj, const QUrl& objUrl) {
      if (!obj && url == objUrl) QCoreApplication::exit(-1);
    },
    Qt::QueuedConnection);
  engine.load(url);

  QObject::connect(&server, &DataServer::errorMessage, &app, [&](const QString& message) {
      QQmlProperty property(engine.rootObjects().at(0), "serverErrorMessage", engine.rootContext());
      property.write(message);
  });
  server.startServer();
  back_end.connect();

  return app.exec();
}
