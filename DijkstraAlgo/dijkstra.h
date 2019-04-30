#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <QString>
#include <QXmlStreamReader>
#include <climits>
#include "supportclasses.h"
#include <QFile>
#include <map>
#include <iostream>
#include <queue>
#include <cmath>
#include <limits>
#include <climits>

#define PI 4.0*atan(1.0)

enum errors{ BAD_ADDRESS  };


using namespace std;



class dijkstra
{

    public:
        dijkstra();
        ~dijkstra();

    private:
    vector<indexo> *graph;
    vertex *allVertexes;
    map<coordinates, int> legend;
    map<QString,map<coordinates, vector<coordinates> >  > closest;

    coordinates focus;

    void readIn();
    coordinates closestOne(const coordinates &noFind, const QString &streetName, const QString &zipCode);
    double performHaversine(const coordinates &one, const coordinates &two);

    public:
        void perform(const QString &lat, const QString &lon, const QString &streetName);
        void statusReport();
};

dijkstra::dijkstra()
{
    graph = new vector<indexo>[80000];
    allVertexes = new vertex[80000];
    legend = map<coordinates,int>();
    readIn();
}

void dijkstra::readIn()
{
    QXmlStreamReader input;
    QFile toOpen;
    toOpen.setFileName("distances6.xml");
    toOpen.open(QFile::ReadOnly);
    input.setDevice(&toOpen);
    input.readNextStartElement();
    input.readNextStartElement();

    QString street;
    coordinates one, two;
    int rank1, rank2;
    double weight;

    while(!input.atEnd())
    {
        if(input.name() == "STREET")
        {
            coordinates addressRange;


            input.readNextStartElement();
            street = input.readElementText();

            input.readNextStartElement();
            street += (" " + input.readElementText());

            input.readNextStartElement();

            while(input.name().toString().toStdString() == "FROM_ADDRESSES")
            {
                addressRange.lattitude = input.readElementText();

                input.readNextStartElement();
                addressRange.longitude = input.readElementText();

                input.readNextStartElement();
                while(input.name() == "EDGE")
                {

                    input.readNextStartElement();
                    input.readNextStartElement();

                    one.lattitude = input.readElementText();
                    input.readNextStartElement();

                    one.longitude = input.readElementText();
                    input.readNextStartElement();

                    rank1 = input.readElementText().toInt();
                    input.readNextStartElement(); //from vertex

                     input.readNextStartElement();

                    weight = input.readElementText().toDouble();
                    input.readNextStartElement();

                    input.readNextStartElement();

                    two.lattitude = input.readElementText();
                    input.readNextStartElement();

                    two.longitude = input.readElementText();
                    input.readNextStartElement();

                    rank2 = input.readElementText().toInt();
                    input.readNextStartElement();

                    graph[rank1].push_back(indexo(rank2,weight));
                    graph[rank2].push_back(indexo(rank1,weight));
                    legend[one] = rank1;
                    legend[two] = rank2;
                    if(!closest[street].count(one))
                        closest[street][addressRange] = vector<coordinates>();
                    closest[street][addressRange].push_back(one);
                    closest[street][addressRange].push_back(two);

                    input.readNextStartElement();
                    input.readNextStartElement();
//                    cout << "ended with: " << input.name().toString().toStdString() << endl;
                    if(input.name() == "FROM_ADDRESSES")
                        break;
                }
            }
        }
        input.readNextStartElement();
    }
    statusReport();
}

void dijkstra::perform(const QString &lat, const QString &lon, const QString &streetName)
{
    coordinates toSearch(lat,lon);
    int pos = legend[toSearch];   
    allVertexes[pos].shortestPath = 0;
    priority_queue<vertex> pq;
    pq.push(allVertexes[pos]);
    while(!pq.empty())
    {
        vertex v = pq.top();
        pq.pop();
        if(!v.visited)
        {
            allVertexes[v.rank].visited = true;
            for(unsigned int i = 0; i < graph[v.rank].size(); ++i)
            {
                int curr = graph[v.rank][i].whereto;
                if(allVertexes[curr].shortestPath > (v.shortestPath + graph[v.rank][i].distance))
                {
                    allVertexes[curr].shortestPath = (v.shortestPath + graph[v.rank][i].distance);
                    allVertexes[curr].previous = v.rank;
                    pq.push(allVertexes[curr]);
                }
            }
        }
    }
}

//note to self, -1 indicates that the address is not possible, otherwise it gives a coordinate
coordinates dijkstra::closestOne(const coordinates &noFind, const QString &streetName, const QString &zipCode)
{
    if(closest[streetName].begin()->first.lattitude > zipCode || closest[streetName].end()->first.lattitude < zipCode )
        throw BAD_ADDRESS;
    else
    {
        closest[streetName][noFind] = vector<coordinates>();
        coordinates toReturn;
        auto pos = closest[streetName].find(noFind);
        --pos;
        unsigned int shortest = 0;
        double shortestPath = numeric_limits<double>::max(), hold;
        for(unsigned int i = 0; i < pos->second.size(); ++i)
        {
            if((hold = performHaversine(pos->second[i], noFind)) < shortestPath)
            {
                shortestPath = hold;
                shortest = i;
            }
        }
        toReturn = pos->second[shortest];
        closest[streetName].erase(++pos);
        return toReturn;
    }
}

void dijkstra::statusReport()
{
    cout << legend.size() << endl;
    cout << closest.size() << endl;

}
dijkstra::~dijkstra()
{
    delete []allVertexes;
    delete []graph;
}


double dijkstra::performHaversine(const coordinates &one, const coordinates &two)
{
   double lat1 = one.lattitude.toDouble() * (PI/180.), long1 = one.longitude.toDouble() * (PI/180.);
   double lat2 = two.lattitude.toDouble() * (PI/180.), long2 = two.longitude.toDouble()* (PI/180.),
           dLat = lat2 - lat1, dLong = long2 - long1;
   double computation = asin(sqrt(sin(dLat / 2.) * sin(dLat / 2.) + cos(lat1) * cos(lat2) * sin(dLong / 2.) * sin(dLong / 2.)));
   double d = 3959.9 * 2 * computation;
   return d;
}

#endif // DIJKSTRA_H
