#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <functional>
#include "echoserver.h"
float randf(float range)
{
    return ((float)(rand() % 10000)) / 10000.0 * range;
}
Point randp(float range)
{
    return Point(randf(range -range /2),randf(range - range/2),randf(range - range /2),randf(range - range/2));
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: echoserver");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    QCommandLineOption portOption(QStringList() << "p" << "port",
            QCoreApplication::translate("main", "Port for echoserver [default: 1234]."),
            QCoreApplication::translate("main", "port"), QLatin1Literal("1234"));
    parser.addOption(portOption);
    parser.process(a);
    bool debug = parser.isSet(dbgOption);
    int port = parser.value(portOption).toInt();

    PointCloudServer *server = new PointCloudServer(port, debug);
    QObject::connect(server, &PointCloudServer::closed, &a, &QCoreApplication::quit);
    QObject::connect(server,&PointCloudServer::newConnect,[&] () {
        QVector<Point> pcl;
        for (int i = 0;i<1000;i++)
        {
            pcl.append( randp(1000));
        }
        server->BoardcastPointCloud(pcl);
    });

    return a.exec();
}
