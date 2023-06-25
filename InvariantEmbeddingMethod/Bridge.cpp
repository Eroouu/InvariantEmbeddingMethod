#include "Bridge.h"
Bridge::Bridge() :Base()
{
	q_con = 1.;
	EI_x = 1.;
}
Bridge::Bridge(double tempQcon, double tempEIx, double tempQ, double tempL, double tempH) :Base(tempQ, tempL, tempH)
{
	q_con = tempQcon;
	EI_x = tempEIx;
}
double Bridge::p(double x)
{
	return 1./(EI_x) * (q_con * x * get_l() / 2 - q_con * x * x / 2);
}

double Bridge::r(double x)
{
	double k = -get_q();
	//return sqrt(k) * (exp(2 * sqrt(k) * l) + 1) / (exp(2 * sqrt(k) * l) - 1);
	return 1. / x;
}

double Bridge::TrueY(double x)
{
	//double ans = 1. / (-q) * ((1 - exp(q * x / p(x, 1))) / (exp(q / p(x,1)) - 1) + x);
	//double ans = -(1. / 24) * q_con * x * x * x * x / EI_x + l*(1. / 12) * q_con * x * x * x / EI_x - (1. / 24)*l*l*l* q_con * x / EI_x;
	double ans = -(1. / 24) * q_con * (x * x * x * x - 2 * get_l() * x * x * x + get_l() * get_l() * get_l() * x) / EI_x;
	return ans;
}



