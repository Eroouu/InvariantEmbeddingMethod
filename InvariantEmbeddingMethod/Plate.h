#pragma once
#include "Base.h"
class Plate :
    public Base
{
public:
	Plate();
	Plate(double q_v, double lambda, double q, double l, double h);
	double r(double x);
	double p(double x);
	double TrueY(double x);
protected:

private:
	double q_v;
	double lambda;
};

