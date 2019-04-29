#include <QCoreApplication>
#include <dijkstra.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout << "?\n";
    dijkstra wtf(QString::fromStdString("shit"), QString::fromStdString("fuck"));


    return 0;
    //return a.exec();
}
