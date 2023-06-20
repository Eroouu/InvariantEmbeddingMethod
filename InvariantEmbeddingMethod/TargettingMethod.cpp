#include "TargettingMethod.h"

TargettingMethod::TargettingMethod()
{
    q_con = 1.;
    EI_x = 1.;
    h = 0.05;
    l = 1;
}

TargettingMethod::TargettingMethod(double tempQcon, double tempEIx, double tempL, double tempH)
{
    q_con = tempQcon;
    EI_x = tempEIx;
    h = tempH;
    l = tempL;
}

double TargettingMethod::TrueY(double x)
{
	//double ans = 1. / (-q) * ((1 - exp(q * x / p(x, 1))) / (exp(q / p(x,1)) - 1) + x);
	//double ans = -(1. / 24) * q_con * x * x * x * x / EI_x + l*(1. / 12) * q_con * x * x * x / EI_x - (1. / 24)*l*l*l* q_con * x / EI_x;
	double ans = -(1. / 24) * q_con * (x * x * x * x - 2 * l * x * x * x + l * l * l * x) / EI_x;
	return ans;
}

double TargettingMethod::F(double z, double tempL, double v)
{
    return (q_con * tempL * z / 2. - q_con * z * z / 2.) / EI_x + v;
}

double TargettingMethod::FindP()
{
    double p1 = 200, p2 = -100;
    double tempP;
    while (abs(RuK(l, p1)) > 1e-12)
    {
        //cout << RuK(l, p1) << " " << p1 << endl;
        tempP = (p2 + p1) / 2.;
        if (RuK(l, p1) * RuK(l, tempP) < 0)
            p2 = tempP;
        else if (RuK(l, tempP) * RuK(l, p2) < 0)
            p1 = tempP;
    }
    //cout << "p is: " << p1 << endl;
    p = p1;
    return p;
}

double TargettingMethod::RuK(double tempL, double tempP)
{
    double x0, v0, un, u0, vn, k0, k1, k2, k3, g;
    x0 = 0;
    un = u0 = 0;
    vn = v0 = tempP;
    for (int i = 0; i < tempL/h+1; i++)
    {
        x0 = i * h;
        k0 = v0 + h * F(x0, tempL, v0);
        k1 = v0 + h * F(x0 + h / 2., tempL, v0 + h * k0 / 2.);
        k2 = v0 + h * F(x0 + h / 2., tempL, v0 + h * k1 / 2.);
        k3 = v0 + h * F(x0 + h, tempL, v0 + h * k2);
        un = u0 + (h / 6.) * (k0 + 2. * k1 + 2. * k2 + k3);
        vn = k0;
        u0 = un;
        v0 = vn;
    }

    return un;
}
