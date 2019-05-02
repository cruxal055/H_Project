#include <QCoreApplication>
#include <dijkstra.h>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
   dijkstra temp;
   temp.perform("34.12416049793684", "-118.21936667211293", "where");
//   temp.perform("34.112015756932813", "-118.201564947701129", "where");
   temp.getShortestPath("34.112015756932813", "-118.201564947701129");



    return 0;
    //return a.exec();
}
