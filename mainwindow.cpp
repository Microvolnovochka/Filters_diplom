#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aircraftmodel.h"
#include "abfilter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int n = 60;
    QVector <double> x(n),y(n),t(n),nX(n),nY(n),alX(n),alY(n);
    aircraftModel *plane = new aircraftModel (5000,3000,1,10,-20,2.0,-1.0);
    AB_Filter *ab = new AB_Filter(5000,3000,1,40,-10,0,0);
    for (int i =0 ;i<n; i++)
    {
        x[i] = plane->getX();
        y[i] = plane->getY();
        nX[i] = plane->getNX();
        nY[i] = plane->getNY();
        ab->setZXZY(nX[i],nY[i]);
        ab->update(0.5,0.4,0.1,false);
        alX[i] = ab->getX();
        alY[i] = ab->getY();
        qDebug() << x[i] <<y[i]  << "/" <<  plane->getVX()<< plane->getVY();
        t[i] = i;
        plane->update();
    }
    ui->plotX->addGraph();
    ui->plotX->graph(0)->setData(t,x);
    ui->plotX->addGraph();
    ui->plotX->graph(1)->setData(t,nX);
    ui->plotX->addGraph();
    ui->plotX->graph(2)->setPen(QPen(Qt::green));
    ui->plotX->graph(2)->setData(t,alX);
    ui->plotX->xAxis->setLabel("time, s");
    ui->plotX->yAxis->setLabel("x");
    ui->plotX->xAxis->setRange(0,n);
    ui->plotX->yAxis->setRange(4000,9000);
    ui->plotX->replot();
    ui->plotY->addGraph();
    ui->plotY->graph(0)->setData(t,y);
    ui->plotY->addGraph();
    ui->plotY->graph(1)->setData(t,nY);
    ui->plotY->addGraph();
    ui->plotY->graph(2)->setPen(QPen(Qt::green));
    ui->plotY->graph(2)->setData(t,alY);
    ui->plotY->xAxis->setLabel("time, s");
    ui->plotY->yAxis->setLabel("y");
    ui->plotY->xAxis->setRange(0,n);
    ui->plotY->yAxis->setRange(0,3000);
    ui->plotY->replot();
    ui->plotXY->addGraph();
    ui->plotXY->graph(0)->setData(x,y);
    ui->plotXY->xAxis->setLabel("x");
    ui->plotXY->yAxis->setLabel("y");
    ui->plotXY->xAxis->setRange(0,6000);
    ui->plotXY->yAxis->setRange(0,8000);
    ui->plotXY->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

