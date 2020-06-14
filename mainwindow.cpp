#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aircraftmodel.h"
#include "abfilter.h"
#include "kalmanfilter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int n = 200;
    QVector <double> x(n),y(n),t(n),nX(n),nY(n),abX(n),abY(n),kX(n),kY(n),abeX(n),abeY(n),keX(n),keY(n);
    double skoabX = 0,skoabY = 0,skokX = 0,skokY = 0;
    aircraftModel *plane = new aircraftModel (5000,8000,1,10,-10,2.0,-1.0);
    KalmanFilter *kf = new KalmanFilter(4,2);
    kf->alloc_filter(4000,9000,1,0,0,150,2.0,-1.0);
    AB_Filter *ab = new AB_Filter(4000,9000,1,0,0,0,0);
    for (int i =0 ;i<n; i++)
    {
        plane->update();
        x[i] = plane->getX();
        y[i] = plane->getY();
        nX[i] = plane->getNX();
        nY[i] = plane->getNY();
        ab->setMXMY(nX[i],nY[i]);
        kf->setObservation(nX[i],nY[i]);
        ab->update(0.3,0.1);
        kf->update();
        abX[i] = ab->getX();
        abY[i] = ab->getY();
        kX[i] = kf ->getX();
        kY[i] = kf ->getY();
        abeX[i] = abs(x[i] - abX[i]);
        abeY[i] = abs(y[i] - abY[i]);
        keX[i] = abs(x[i] - kX[i]);
        keY[i] = abs(y[i] - kY[i]);
        skoabX += abeX[i];
        skoabY += abeY[i];
        skokX += keX[i];
        skokY += keY[i];
        qDebug() << x[i] <<y[i]  << "/" << kX[i] << kY[i];
        t[i] = i*2;
    }
    kf->free_filter();
    skoabX /= n;
    skoabY /= n;
    skokX /= n;
    skokY /= n;
    qDebug() << skoabX << skoabY << "/" << skokX << skokY;
    ui->plotX->addGraph();
    ui->plotX->graph(0)->setData(t,x);
    ui->plotX->addGraph();
    ui->plotX->graph(1)->setData(t,nX);
    ui->plotX->addGraph();
    ui->plotX->graph(2)->setPen(QPen(Qt::green));
    ui->plotX->graph(2)->setData(t,abX);
    ui->plotX->addGraph();
    ui->plotX->graph(3)->setPen(QPen(Qt::red));
    ui->plotX->graph(3)->setData(t,kX);
    ui->plotX->xAxis->setLabel("time, s");
    ui->plotX->yAxis->setLabel("x");
    ui->plotX->xAxis->setRange(0,n);
    ui->plotX->yAxis->setRange(4000,6000);
    ui->plotX->replot();
    ui->plotY->addGraph();
    ui->plotY->graph(0)->setData(t,y);
    ui->plotY->addGraph();
    ui->plotY->graph(1)->setData(t,nY);
    ui->plotY->addGraph();
    ui->plotY->graph(2)->setPen(QPen(Qt::green));
    ui->plotY->graph(2)->setData(t,abY);
    ui->plotY->addGraph();
    ui->plotY->graph(3)->setPen(QPen(Qt::red));
    ui->plotY->graph(3)->setData(t,kY);
    ui->plotY->xAxis->setLabel("time, s");
    ui->plotY->yAxis->setLabel("y");
    ui->plotY->xAxis->setRange(0,n);
    ui->plotY->yAxis->setRange(7000,9000);
    ui->plotY->replot();
    ui->plotEX->addGraph();
    ui->plotEX->graph(0)->setData(t,abeX);
    ui->plotEX->addGraph();
    ui->plotEX->graph(1)->setPen(QPen(Qt::red));
    ui->plotEX->graph(1)->setData(t,keX);
    ui->plotEX->xAxis->setLabel("time, s");
    ui->plotEX->yAxis->setLabel("error");
    ui->plotEX->xAxis->setRange(0,n);
    ui->plotEX->yAxis->setRange(0,200);
    ui->plotEX->replot();
    ui->plotEY->addGraph();
    ui->plotEY->graph(0)->setData(t,abeY);
    ui->plotEY->addGraph();
    ui->plotEY->graph(1)->setPen(QPen(Qt::red));
    ui->plotEY->graph(1)->setData(t,keY);
    ui->plotEY->xAxis->setLabel("time, s");
    ui->plotEY->yAxis->setLabel("error");
    ui->plotEY->xAxis->setRange(0,n);
    ui->plotEY->yAxis->setRange(0,100);
    ui->plotEY->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

