#pragma once
#include "Base.h"
class Plate :
    public Base
{
public:
	Plate();
	Plate(double q_v, double lambda, double q, double l, double h);
	Plate(double T0, double q_v, double lambda, double q, double l, double h);
	double r(double x);
	virtual double p(double x);
	vector<double> get_ans();
	virtual double TrueY(double x);
protected:
	double lambda;
	double T0;
private:
	double q_v;
	
};

