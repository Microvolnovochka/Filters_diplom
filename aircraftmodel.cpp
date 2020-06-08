#include "aircraftmodel.h"

#include <time.h>

aircraftModel::aircraftModel(double _x,double _y, double _dt, double _vX, double _vY, double _aX, double _aY)
{
    this->x = _x;
    this->y = _y;
    this->vX = _vX;
    this->vY = _vY;
    this->dt = _dt;
    this->aX = _aX;
    this->aY = _aY;
    srand (time(NULL));
}

void aircraftModel::update()
{
   this->x += this->vX*this->dt + this->aX*(pow(this->dt,2.0)/2.0);
   this->y += this->vY*this->dt + this->aY*(pow(this->dt,2.0)/2.0);
   this->vX += this->aX*this->dt;
   this->vY += this->aY*this->dt;
}

void aircraftModel::update(double angle)
{
    double radAngle = angle/180 * PI;
    this->x += this->vX*(sin(radAngle*this->dt)/radAngle) -  this->vY*(-(1 - cos(radAngle*this->dt))/radAngle);
    this->y += this->vX*((1 - cos(radAngle*this->dt))/radAngle) - this->vY*(sin(radAngle*this->dt)/radAngle);
    this->vX = this->vX*cos(radAngle*this->dt) - this->vY*sin(radAngle*this->dt);
    this->vY = this->vX*sin(radAngle*this->dt) + this->vY*cos(radAngle*this->dt);
}
double aircraftModel::getX()
{
    return this->x;
}

double aircraftModel::getY()
{
    return this->y;
}

double aircraftModel::getVX()
{
    return this->vX;
}

double aircraftModel::getVY()
{
    return this->vY;
}

double aircraftModel::getNX()
{
    return this->x + rand()%300-150;
}

double aircraftModel::getNY()
{
    return this->y + rand()%300-150;
}

double aircraftModel::getNVX()
{
    return this->x;
}

double aircraftModel::getNVY()
{
    return this->x;
}
