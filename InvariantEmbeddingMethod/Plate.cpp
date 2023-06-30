#include "Plate.h"

Plate::Plate()
{
	q_v = 100;
	lambda = 2;
}

Plate::Plate(double q_v, double lambda, double q, double l, double h):Base(q,l,h)
{
	this->q_v = q_v;
	this->lambda = lambda;
}

double Plate::r(double x)
{
	return 1./x;
}

double Plate::p(double x)
{
	return -q_v/lambda;
}

double Plate::TrueY(double x)
{
	return -q_v*x*x/(2*lambda)+q_v*l*x/(2*lambda);
}
