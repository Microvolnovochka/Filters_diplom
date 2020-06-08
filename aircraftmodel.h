#ifndef AIRCRAFTMODEL_H
#define AIRCRAFTMODEL_H

#include "matrix.h"

class aircraftModel
{
public:
    aircraftModel(double _x,double _y, double _dt, double _vX, double _vY, double _aX = 0, double _aY = 0);

    void update();
    void update (double angle);
    double getX();
    double getY();
    double getVX();
    double getVY();
    double getNX();
    double getNY();
    double getNVX();
    double getNVY();
private:
    double x,y,vX,vY,aX,aY,dt;

};

#endif // AIRCRAFTMODEL_H
