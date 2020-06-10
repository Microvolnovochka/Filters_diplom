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
    int n = 40;
    QVector <double> x(n),y(n),t(n),nX(n),nY(n),abX(n),abY(n),kX(n),kY(n);
    aircraftModel *plane = new aircraftModel (5000,8000,2,10,-10);
    KalmanFilter *kf = new KalmanFilter(4,2);
    kf->alloc_filter(5000,8000,2,0,0,100);
    AB_Filter *ab = new AB_Filter(5000,8000,2,0,0);
    for (int i =0 ;i<n; i++)
    {
        plane->update();
        x[i] = plane->getX();
        y[i] = plane->getY();
        nX[i] = plane->getNX();
        nY[i] = plane->getNY();
        ab->setMXMY(nX[i],nY[i]);
        kf->setObservation(nX[i],nY[i]);
        ab->update(0.3,0.2);
        kf->update();
        abX[i] = ab->getX();
        abY[i] = ab->getY();
        kX[i] = kf ->getX();
        kY[i] = kf ->getY();
        qDebug() << x[i] <<y[i]  << "/" << kX[i] << kY[i];
        t[i] = i;
    }
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

