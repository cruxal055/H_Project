#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QDebug>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    master = new dijkstra[3];
    ui->setupUi(this);
    ui->textEdit->setTextColor(Qt::black);
    this->setWindowTitle("Eagle Rock Fire Stations");
    setupWebEngine();
    setupSignalsAndSlots();
    displayMap();
    master[0].perform("34.12416049793684", "-118.21936667211293", "where");
    //       temp.getShortestPath("34.115197150389598", "-118.224690123437298");
//    master[0].getShortestPath("34.115197150389598", "-118.224690123437298");
}

MainWindow::~MainWindow()
{
    delete []master;
    delete view;
    //delete channel;
    //delete page;
}

void MainWindow::setupSignalsAndSlots()
{
    connect(ui->quitButton,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->loadButton,SIGNAL(clicked(bool)),this,SLOT(loadMap()));
    connect(ui->tester, SIGNAL(clicked(bool)), this, SLOT(testFunc()));
}


void MainWindow::displayMap()
{
    QDir dir("../Resources/map.html");
    //    "⁨Users⁩⁨/blank⁩/⁨Documents⁩/⁨Honors_Project⁩/mapItExample⁩/Contents⁩/⁨Resources/map.html"⁩
    QFileInfo exists("../Resources/map.html");
    if(exists.exists())
    {
        qDebug() << exists.absoluteFilePath() << endl;
        qDebug() << "ya\n";
    }


    page->load(QUrl(QUrl::fromLocalFile(dir.canonicalPath())));
}
void MainWindow::testFunc()
{
    QStack<QString> stuff;
    QString oof = "oof";
    QVariantList temp;
    QJsonObject wtf1, wtf2;
    QJsonArray oofOwie;
    master[0].getShortestPath("34.111065373824573", "-118.2041155298122286"
                                                   );
    if(master[0].shortest.empty())
        qDebug() << "it's empty\n";
    while(!master[0].shortest.empty())
    {
        coordinates temp = master[0].shortest.top();
        master[0].shortest.pop();
        oofOwie.push_back(QJsonValue(temp.lattitude + ", " + temp.longitude));
    }

//    wtf1.insert("stuff", "34.12416049793684, -118.21936667211293");
//    oofOwie.push_back(QJsonValue("34.11202931911081, -118.199139905572622"));
//    oofOwie.push_back(QJsonValue("34.112015756932813, -118.201564947701129"));
//    oofOwie.push_back(QJsonValue("34.12416049793684, -118.21936667211293"));


    /*

     * */

//        temp.push_back(wtf1);
//    temp.push_back(wtf2);
    emit testing(oofOwie);
}

void MainWindow::loadMap()
{
    emit drawMap();
}

void MainWindow::setupWebEngine()
{
    qDebug()<<"starting";
    view = new QWebEngineView;
    view->setParent(ui->centralWidget);
    view->setGeometry(20,20,800,600); //20,20,800,600
    channel = new QWebChannel(view->page());
    //attach it to the QWebEnginePage
    view->page()->setWebChannel(channel);
    //register a QObject to be exposed to JavaScript
    channel->registerObject(QStringLiteral("mainwindow"), this);
    page = view->page();
}

void MainWindow::updateLatLong(const QString &latLng)
{
//    ui->currLatLng->setText("Current position: " + QString::fromStdString("0,0"));


    ui->currLatLng->setText("Current position: " + latLng);
}

