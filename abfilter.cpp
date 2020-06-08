#include "abfilter.h"

AB_Filter::AB_Filter(double _x,double _y, double _dt,double _vX,double _vY,double _aX, double _aY)
{
    this->x = _x;
    this->y = _y;
    this->dt = _dt;
    this->vX = _vX;
    this->vY = _vY;
    this->aX = _aX;
    this->aY = _aY;
    this->zX = _x;
    this->zY = _y;
}

void AB_Filter::setZXZY (double _zX,double _zY)
{
    this->zX = _zX;
    this->zY = _zY;
}

double AB_Filter::getX()
{
    return this->x;
}

double AB_Filter::getY()
{
    return this->y;
}

void AB_Filter::update(double alpha, double beta, bool predict)
{
    this->vX += beta*((this->zX-this->x)/this->dt);
    this->vY += beta*((this->zY-this->y)/this->dt);
    this->x += alpha*(this->zX-this->x);
    this->y += alpha*(this->zY-this->y);
    if (predict)
    {
        this->x += this->vX*this->dt;
        this->y += this->vY*this->dt;
    }
}

void AB_Filter::update(double alpha, double beta,double gamma, bool predict)
{
    this->aX += gamma*((this->zX-this->x)/(0.5*this->dt*this->dt));
    this->aY += gamma*((this->zY-this->y)/(0.5*this->dt*this->dt));
    this->vX += beta*((this->zX-this->x)/this->dt);
    this->vY += beta*((this->zY-this->y)/this->dt);
    this->x += alpha*(this->zX-this->x);
    this->y += alpha*(this->zY-this->y);
    if (predict)
    {
        this->x += this->vX*this->dt + this->aX*((this->dt*this->dt)/2);
        this->y += this->vY*this->dt + this->aY*((this->dt*this->dt)/2);
        this->vX += this->aX*this->dt;
        this->vY += this->aY*this->dt;
    }
}
