#include <QCoreApplication>
#include <dijkstra.h>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
   dijkstra temp;
   temp.perform("34.12416049793684", "-118.21936667211293", "where");

 //   temp.perform("34.112015756932813", "-118.201564947701129", "where");

       temp.getShortestPath("34.115197150389598", "-118.224690123437298");
    //temp.getShortestPath("34.1317701627123", "-118.195737121438455");
   temp.toString();



    return 0;
    //return a.exec();
}
