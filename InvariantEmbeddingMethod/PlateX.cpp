#include "PlateX.h"

PlateX::PlateX()
{
}

PlateX::PlateX(double T0, double lambda, double q, double l, double h):Plate(T0,0,lambda,q,l,h)
{
}
double PlateX::p(double x)
{
	return -func_q_v(x) / lambda;
}
double PlateX::func_q_v(double x)
{
	return 10*x*x;
}
double PlateX::TrueY(double x)
{
	//return -q_v * x * x / (2 * lambda) + q_v * l * x / (2 * lambda);
	return T0-5 * x * x * x * x / (6 * lambda) + 5 * l * l * l * x / (6 * lambda);
}