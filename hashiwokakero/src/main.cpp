#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "boardlogic.hpp"

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<BoardLogic>("ru.deka.bridges", 1, 0, "BoardLogic");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/qt/qml/ui/main.qml"_qs);
    engine.load(url);

    return app.exec();
}
