#pragma once
#include "Plate.h"
class PlateX :
    public Plate
{
public:
    PlateX();
    PlateX(double T0, double lambda, double q, double l, double h);
    double p(double x);
    double func_q_v(double x);
    double TrueY(double x);
protected:
private:
};

