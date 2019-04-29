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


using namespace std;



class dijkstra
{

    public:
        dijkstra(const QString &lat, const QString &lon);
        ~dijkstra();

    private:
    vector<indexo> *graph;
    vertex *allVertexes;
    map<coordinates, int> legend;
    map<QString,map<coordinates, vector<coordinates> >  > closest;

    coordinates focus;

    void readIn();

    public:
        void perform(const QString &lat, const QString &lon);

};

dijkstra::dijkstra(const QString &lat, const QString &lon)
{
    graph = new vector<indexo>[80000];
    allVertexes = new vertex[80000];
    focus = coordinates(lat,lon);
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
    cout << "done\n";
}

void dijkstra::perform(const QString &lat, const QString &lon)
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

dijkstra::~dijkstra()
{
    delete []allVertexes;
    delete []graph;
}



#endif // DIJKSTRA_H
