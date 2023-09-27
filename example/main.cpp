#include <QApplication>
#include <QQmlApplicationEngine>
#include <QThread>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qmlweston"));
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);
    engine.load(url);
    // pass the engine to the inputcontext
    qApp->setProperty("engine",QVariant::fromValue(&engine));
    app.exec();
}
