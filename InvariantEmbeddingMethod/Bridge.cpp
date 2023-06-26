#include "Bridge.h"
Bridge::Bridge() :Base()
{
	q_con = 1.;
	EI_x = 1.;
}
Bridge::Bridge(double q_con, double EI_x, double q, double l, double h, double bc_l, double bc_r):
	Base(q, l, h,bc_l,bc_r)
{
	this->q_con = q_con;
	this->EI_x = EI_x;
}
double Bridge::p(double x)
{
	return 1./(EI_x) * (q_con * x * l / 2 - q_con * x * x / 2);
}

double Bridge::r(double x)
{
	double k = -q;
	//return sqrt(k) * (exp(2 * sqrt(k) * l) + 1) / (exp(2 * sqrt(k) * l) - 1);
	return 1. / x;
}

double Bridge::TrueY(double x)
{
	//double ans = 1. / (-q) * ((1 - exp(q * x / p(x, 1))) / (exp(q / p(x,1)) - 1) + x);
	//double ans = -(1. / 24) * q_con * x * x * x * x / EI_x + l*(1. / 12) * q_con * x * x * x / EI_x - (1. / 24)*l*l*l* q_con * x / EI_x;
	//double ans = -(1. / 24) * q_con * (x * x * x * x - 2 * l * x * x * x + l * l * l * x) / EI_x;
	double ans = (1. / 24) * x * (2 * q_con * l * x * x - q_con * x * x * x) / EI_x -
		(1. / 24) * x * (q_con * l * l * l * l + 24 * EI_x * bc_l - 24 * bc_r * EI_x) / (EI_x * l) + bc_l;
	return ans;
}



