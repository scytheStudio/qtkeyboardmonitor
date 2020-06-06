#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <src/KeyboardMonitor.h>

/*
 * App used to track keyboard usage on Windows
 * More info about how it is achived in KeyboardOmintor.h file
 */

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    KeyboardMonitor* keyboardMonitor = new KeyboardMonitor(&app);

    QQmlApplicationEngine engine;

    //Adding keyboard monitor context by passing poiner to object to engine, so it can be acessed from qml
    engine.rootContext()->setContextProperty("keyboardMonitor", keyboardMonitor);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
