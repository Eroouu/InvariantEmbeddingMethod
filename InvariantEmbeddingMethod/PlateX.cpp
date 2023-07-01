#include "PlateX.h"

PlateX::PlateX()
{
	degree = 2;
	C={0,0,10};
}

PlateX::PlateX(int degree,vector<double> C,double T0, double lambda, double q, double l, double h):Plate(T0,0,lambda,q,l,h)
{
	this->degree = degree;
	this->C = C;
}
double PlateX::p(double x)
{
	return -func_q_v(x) / lambda;
}
double PlateX::func_q_v(double x)
{
	double sum = 0;
	for (int i = 0; i <= degree; i++)
	{
		sum+= C[i] * pow(x, i);
	}	
	return sum;
}
double PlateX::TrueY(double x)
{
	double sum = 0;
	for (int i = 0; i <= degree; i++)
	{
		sum += -C[i] * pow(x, i + 2) / (lambda * (i + 2) * (i + 1)) + C[i] * x * pow(l, i + 1) / (lambda * (i + 2) * (i + 1));
	}
	return T0+sum;
}