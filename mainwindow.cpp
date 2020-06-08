#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aircraftmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int n = 10;
    QVector <double> x(n),y(n),t(n);
    aircraftModel *plane = new aircraftModel (5000,2000,1,150,100);
    for (int i =0 ;i<n; i++)
    {
        x[i] = plane->getX();
        y[i] = plane->getY();
        qDebug() << x[i] <<y[i] << "/" <<  plane->getVX()<< plane->getVY();
        t[i] = i;
        plane->update(36.0);
    }
    ui->plotX->addGraph();
    ui->plotX->graph(0)->setData(t,x);
    ui->plotX->xAxis->setLabel("time, s");
    ui->plotX->yAxis->setLabel("x");
    ui->plotX->xAxis->setRange(0,11);
    ui->plotX->yAxis->setRange(2700,4200);
    ui->plotX->replot();
    ui->plotY->addGraph();
    ui->plotY->graph(0)->setData(t,y);
    ui->plotY->xAxis->setLabel("time, s");
    ui->plotY->yAxis->setLabel("y");
    ui->plotY->xAxis->setRange(0,11);
    ui->plotY->yAxis->setRange(1700,3000);
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

