#include "abfilter.h"

AB_Filter::AB_Filter(double _x,double _y, double _dt,double _vX,double _vY,double _aX, double _aY)
{
    this->x = _x;
    this->x2 = _x;
    this->y = _y;
    this->y2 = _y;
    this->dt = _dt;
    this->vX = _vX;
    this->vY = _vY;
    this->vX2 = _vX;
    this->vY2 = _vY;
    this->aX = _aX;
    this->aY = _aY;
    this->aX2 = _aX;
    this->aY2 = _aY;
}

double AB_Filter::getX()
{
    return this->x2;
}

double AB_Filter::getY()
{
    return this->y2;
}

void AB_Filter::setMXMY(double _mX, double _mY)
{
    this->mX = _mX;
    this->mY = _mY;
}

void AB_Filter::update(double alpha, double beta)
{
    x = x2 + vX2 * dt;
    y = y2 + vY2 * dt;
    vX = vX2;
    vY = vY2;
    x2 = x + alpha*(mX-x);
    y2 = y + alpha*(mY-y);
    vX2 = vX + beta*(mX-x)/dt;
    vY2 = vY + beta*(mY-y)/dt;
}

void AB_Filter::update(double alpha, double beta,double gamma)
{
    x = x2 + vX2 * dt + (aX2*dt*dt)/2;
    y = y2 + vY2 * dt + (aY2*dt*dt)/2;
    vX = vX2 + aX2 * dt;
    vY = vY2 + aY2 * dt;
    aX = aX2;
    aY = aY2;
    x2 = x + alpha*(mX-x);
    y2 = y + alpha*(mY-y);
    vX2 = vX + beta*(mX-x)/dt;
    vY2 = vY + beta*(mY-y)/dt;
    aX2 = aX + (2*gamma/(dt*dt))*(mX-x);
    aY2 = aY + (2*gamma/(dt*dt))*(mY-y);
}
