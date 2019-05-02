#ifndef SUPPORTCLASSES_H
#define SUPPORTCLASSES_H
#include <QString>
#include <climits>

using namespace std;

struct indexo
{
    double distance;
    int whereto;

    indexo()
    {
        distance = -1.;
        whereto = -1;
    }

    indexo(int whereTo, double distance)
    {
        this->distance = distance;
        this->whereto = whereTo;
    }

    indexo(const indexo &other)
    {
        distance = other.distance;
        whereto = other.whereto;
    }

    indexo& operator=(const indexo &other)
    {
        if(this != &other)
        {
            distance = other.distance;
            whereto = other.whereto;
        }
        return *this;
    }
};


struct coordinates
{
    public:
        QString lattitude, longitude;
        coordinates()
        {
            lattitude = longitude = "";
        }

        coordinates(const QString &lat, const QString &lon)
        {
            lattitude = lat;
            longitude = lon;
        }

        coordinates &operator=(const coordinates &other)
        {
            if(this != &other)
            {
                lattitude = other.lattitude;
                longitude = other.longitude;
            }
            return *this;
        }

        coordinates(const coordinates &other)
        {
            lattitude = other.lattitude;
            longitude = other.longitude;
        }

        friend bool operator<=(const coordinates &o1 ,const coordinates &o2)
        {
            return o1.lattitude <= o2.lattitude;
        }

        friend bool operator>=(const coordinates &o1 ,const coordinates &o2)
        {
            return o1.lattitude >= o2.lattitude;
        }
        friend bool operator>(const coordinates &o1 ,const coordinates &o2)
        {
            return o1.lattitude > o2.lattitude;
        }
        friend bool operator<(const coordinates &o1 ,const coordinates &o2)
        {
            return (o1.lattitude.toDouble() + o1.longitude.toDouble()) < (o2.lattitude.toDouble()+ o2.longitude.toDouble());
        }
        friend bool operator==(const coordinates &o1 ,const coordinates &o2)
        {
            return o1.lattitude ==  o2.lattitude && o2.longitude == o1.longitude;
        }
};



struct address
{
    public:
        QString lattitude, longitude;
        address()
        {
            lattitude = longitude = "";
        }
        address(const QString &lat)
        {
            lattitude = lat;
            longitude = "";
        }

        address(const QString &lat, const QString &lon)
        {
            lattitude = lat;
            longitude = lon;
        }

        address &operator=(const address &other)
        {
            if(this != &other)
            {
                lattitude = other.lattitude;
                longitude = other.longitude;
            }
            return *this;
        }

        address(const address &other)
        {
            lattitude = other.lattitude;
            longitude = other.longitude;
        }

        friend bool operator<=(const address &o1 ,const address &o2)
        {
            return o1.lattitude <= o2.lattitude;
        }

        friend bool operator>=(const address &o1 ,const address &o2)
        {
            return o1.lattitude >= o2.lattitude;
        }
        friend bool operator>(const address &o1 ,const address &o2)
        {
            return o1.lattitude > o2.lattitude;
        }
        friend bool operator<(const address &o1 ,const address &o2)
        {
            return o1.lattitude < o2.lattitude;
        }
        friend bool operator==(const address &o1 ,const address &o2)
        {
            return o1.lattitude ==  o2.lattitude;
        }
};
struct vertex
{
    int rank, previous;
    coordinates coordinate;
    bool visited;
    double shortestPath;

    vertex();
    vertex(const vertex &other);
    vertex& operator=(const vertex &other);

    friend bool operator<=(const vertex &one, const vertex &two);
    friend bool operator>=(const vertex &one, const vertex &two);
    friend bool operator<(const vertex &one, const vertex &two);
    friend bool operator>(const vertex &one, const vertex &two);


};

vertex::vertex()
{
    rank = previous = -1;
    coordinate = coordinates();
    visited = false;
    shortestPath = numeric_limits<double>::max();
}

vertex::vertex(const vertex &other)
{
    rank = other.rank;
    coordinate = other.coordinate;
    visited = other.visited;
    shortestPath = other.shortestPath;
}
vertex& vertex::operator=(const vertex &other)
{
    if(this != &other)
    {
        rank = other.rank;
        coordinate = other.coordinate;
        visited = other.visited;
        shortestPath = other.shortestPath;
    }
    return *this;
}

bool operator<=(const vertex &one, const vertex &two)
{
    return one.shortestPath >= two.shortestPath;
}

bool operator>=(const vertex &one, const vertex &two)
{
    return one.shortestPath <= two.shortestPath;
}

bool operator<(const vertex &one, const vertex &two)
{
    return one.shortestPath > two.shortestPath;
}

bool operator>(const vertex &one, const vertex &two)
{
    return one.shortestPath < two.shortestPath;
}





#endif // SUPPORTCLASSES_H
