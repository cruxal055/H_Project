#include <QCoreApplication>
#include <iostream>
#include <QXmlStreamReader>
#include <map>
#include <QFile>


using namespace std;

struct coordinates
{
    public:
        double lattitude, longitude;
};

class street
{
    public:
        street();
        int fromAddress, toAddress, streetNum, zipCode;
        string streetName, streetSFX;
        char direction;
        vector<coordinates> waypoints;

};
street::street()
{
    fromAddress = toAddress = streetNum = zipCode = 0;
    streetName = streetSFX = "";
    direction = ' ';
}

int main(int argc, char *argv[])
{
   /* street::street()
    {
        map<string, street> data;
        QXmlStreamReader read("streets2.xml");
        while(!read.atEnd())
        {


        }


    }*/

    /**
     * @<STREET>
    <FROM_ADDRESS>4501</FROM_ADDRESS>
    <TO_ADDRESS>4598</TO_ADDRESS>
    <STNAME>PAULHAN</STNAME>
    <STNUM>3627</STNUM>
    <STSFX>AVE</STSFX>
    <TDIR>N</TDIR>
    <ZIP_L>90041</ZIP_L>
    <COORDINATES>
        <WAYPOINT>
            <LATITUDE>34.125770823425128</LATITUDE>
            <LONGITUDE>-118.218592285979938</LONGITUDE>
        </WAYPOINT>
        <WAYPOINT>
            <LATITUDE>34.126667652875312</LATITUDE>
            <LONGITUDE>-118.215748316593235</LONGITUDE>
        </WAYPOINT>
    </COORDINATES>
</STREET>
     */
    QFile stream;
    stream.setFileName("streets2.xml");
    stream.open(QFile::ReadOnly | QFile::Text);
    map<string,street> master;
    QXmlStreamReader streamer;
    streamer.setDevice(&stream);
    streamer.readNext();
    while(!streamer.atEnd() && streamer.readNextStartElement())
    {
        string item;
        street temp;
        if(streamer.name() == "STREET")
        {
            streamer.readNextStartElement();
            temp.fromAddress = streamer.readElementText().toInt();

            streamer.readNextStartElement();
            temp.toAddress = streamer.readElementText().toInt();

            streamer.readNextStartElement();
            temp.streetName = streamer.readElementText().toStdString();

            streamer.readNextStartElement();
            temp.streetNum = streamer.readElementText().toInt();

            streamer.readNextStartElement();
            temp.streetSFX = streamer.readElementText().toStdString();

            streamer.readNextStartElement();
            temp.direction = streamer.readElementText()[0].toLatin1();


            streamer.readNextStartElement();
            temp.zipCode = streamer.readElementText().toInt();

            streamer.readNextStartElement();
            streamer.readNextStartElement();

            streamer.readNextStartElement();
            cout << " HELLO: " << streamer.name().toString().toStdString() << endl;
            streamer.readNextStartElement();
            cout << " HELLO: " << streamer.name().toString().toStdString() << endl;
            streamer.readNextStartElement();
            cout << " HELLO: " << streamer.name().toString().toStdString() << endl;
            streamer.readNextStartElement();
            cout << " HELLO: " << streamer.name().toString().toStdString() << endl;
            streamer.readNextStartElement();
            cout << " HELLO: " << streamer.name().toString().toStdString() << endl;
            streamer.readNextStartElement();
            cout << " HELLO: " << streamer.name().toString().toStdString() << endl;
            streamer.readNextStartElement();
            cout << " HELLO: " << streamer.name().toString().toStdString() << endl;
            streamer.readNextStartElement();
            cout << " HELLO: " << streamer.name().toString().toStdString() << endl;
            cout << " HELLO: " << streamer.name().toString().toStdString() << endl;
            streamer.readNextStartElement();
            cout << " HELLO: " << streamer.name().toString().toStdString() << endl;
            streamer.readNextStartElement();
            cout << " HELLO: " << streamer.name().toString().toStdString() << endl;
            streamer.readNextStartElement();
            cout << " HELLO: " << streamer.name().toString().toStdString() << endl;
            streamer.readNextStartElement();
            cout << " HELLO: " << streamer.name().toString().toStdString() << endl;
            streamer.readNextStartElement();
            cout << " HELLO: " << streamer.name().toString().toStdString() << endl;
            streamer.readNextStartElement();
            cout << " HELLO: " << streamer.name().toString().toStdString() << endl;
            streamer.readNextStartElement();
            cout << " HELLO: " << streamer.name().toString().toStdString() << endl;

            //while(streamer.name() == "WAYPOINT")
            //{
                streamer.readNextStartElement();
                cout << " HELLOL: " << streamer.name().toString().toStdString() << endl;
                cout << " HELLOL: " << streamer.name().toString().toStdString() << endl;
                cout << " HELLOL: " << streamer.name().toString().toStdString() << endl;




            //}


        }
    }

    cout << "ay\n";
    return 0;
}
