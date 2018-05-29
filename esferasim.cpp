#include "esferasim.h"
#include <QDebug>
#define PI 3.14159265358979323846264338

EsferaSim::EsferaSim(float x, float y, float r):px(x),py(y),rad(r),ax(0), ay(0)
{
    srand((unsigned)time(NULL));
    float ro = 0.01;  //maximo coeficientede friccion  desde 0 hasta 0.01
    float k = (sin((float)rand())+1)*0.00005;
    vx =(sin(((float)rand())+1)*150.0);
    vy =(sin((float)rand())+1)*150.0;
    masa = 50+(rand()%601-50);
    e = ((sin((float)rand())-1)*0.2)-0.5;
    K = ro*k*PI/2.0;
}

EsferaSim::~EsferaSim()
{

}

void EsferaSim::setVel(float x, float y)
{
    vx=x;
    vy=y;
}

void EsferaSim::setPoint(float x, float y)
{
    px=x;
    py=y;
}


void EsferaSim::actualizar(float dt)
{
    float v = sqrt(pow((vx),2)+pow((vy),2));
    float theta = atan2(vy,vx);
    ax = -1*(K*v*v*rad*rad*cos(theta))/masa;
    ay = (-1*(K*v*v*rad*rad*sin(theta))/masa) - 10;
    px+=vx*dt + (ax/2)*pow(dt,2);
    py+=vy*dt + (ay/2)*pow(dt,2);
    vx+=ax*dt;
    vy+=ay*dt;
}

float EsferaSim::getX() const
{
    return px;
}

float EsferaSim::getY() const
{
    return py;
}

float EsferaSim::setY(float y)
{
    py = y;
}

float EsferaSim::getR() const
{
    return rad;
}

float EsferaSim::getVx() const
{
    return vx;
}

float EsferaSim::getVy() const
{
    return vy;
}

float EsferaSim::get_e() const
{
    return e;
}




