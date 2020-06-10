#ifndef AB_H
#define AB_H


class AB_Filter
{
public:
    AB_Filter(double _x,double _y, double _dt,double _vX,double _vY,double _aX = 0.0, double _aY = 0.0);
    void update(double alpha,double beta);
    void update(double alpha,double beta,double gamma);
    void setMXMY(double _mX,double _mY);
    double getX();
    double getY();
private:
    double x,y,vX,vY,aX,aY,mX,mY,dt;
    double x2,y2,vX2,vY2,aX2,aY2;
};

#endif // AB_H
