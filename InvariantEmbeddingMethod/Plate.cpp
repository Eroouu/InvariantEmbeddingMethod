#include "Plate.h"

Plate::Plate()
{
	
	lambda = 2;
	q_v = 20;
}

Plate::Plate(double q_v, double lambda, double q, double l, double h):Base(q,l,h)
{
	
	this->lambda = lambda;
	this->q_v = q_v;
}

double Plate::r(double x)
{
	return 1./x;
}

double Plate::p(double x)
{
	return -q_v / lambda;
}

double Plate::func_q_v(double x)
{
	return 0.0;
}



double Plate::TrueY(double x)
{
	return -q_v * x * x / (2 * lambda) + q_v * l * x / (2 * lambda);
	//return -5 * x * x * x * x / (6 * lambda) + 5 * l * l * l * x / (6 * lambda);
}
