#pragma once
#include "Base.h"
class Plate :
    public Base
{
public:
	Plate();
	Plate(double q_v, double lambda, double q, double l, double h);
	double r(double x);
	virtual double p(double x);
	virtual double func_q_v(double x);
	virtual double TrueY(double x);
protected:
	double lambda;
private:
	double q_v;
	
};

