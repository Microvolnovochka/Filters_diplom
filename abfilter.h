#ifndef AB_H
#define AB_H


class AB_Filter
{
public:
    AB_Filter(double _x,double _y, double _dt,double _vX,double _vY,double _aX = 0.0, double _aY = 0.0);
    void update(double alpha,double beta,bool predict);
    void update(double alpha,double beta,double gamma,bool predict);
    void setZXZY (double _zX, double _zY);
    double getX();
    double getY();
private:
    double x,y,vX,vY,aX,aY,zX,zY,dt;
};

#endif // AB_H
