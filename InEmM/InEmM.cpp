// InEmM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
using namespace std;

double q = 800.;
double EI_x = 2.;
double temp_l = 1.;
double F(double z, double l, double v)
{
    return (q * l * z / 2. - q * z * z / 2.) / EI_x + v;
}

double True_Answer(double x)
{
    return (-50 / 3) * (x*x*x*x - 2 * x*x*x + x);
}

double RuK(double l, double p)
{
    double n = 1e5;
    double h = l / n;
    double x0, v0, un, u0, vn, k0, k1, k2, k3, g;
    x0 = 0;
    un = u0 = 0;
    vn = v0 = p;
    for (int i = 0; i < n; i++)
    {
        x0 = i * h;
        k0 = v0 + h * F(x0, l, v0);
        k1 = v0 + h * F(x0 + h / 2., l, v0 + h * k0 / 2.);
        k2 = v0 + h * F(x0 + h / 2., l, v0 + h * k1 / 2.);
        k3 = v0 + h * F(x0 + h, l, v0 + h * k2);
        un = u0 + (h / 6.) * (k0 + 2. * k1 + 2. * k2 + k3);
        vn = k0;
        u0 = un;
        v0 = vn;
    }

    return un;
}

double Targetting_Method(double l)
{
    double p1 = 200, p2 = -100;
    double p;
    while (abs(RuK(l, p1)) > 1e-12)
    {
        //cout << RuK(l, p1) << " " << p1 << endl;
        p = (p2 + p1) / 2.;
        if (RuK(l, p1) * RuK(l, p) < 0)
            p2 = p;
        else if (RuK(l, p) * RuK(l, p2) < 0)
            p1 = p;
    }
    cout << "p is: " << p1 << endl;
    return p1;
}



int main()
{
    int k;
    double p = Targetting_Method(1.);
    double k0, k1, k2, k3;
    double n = 1e4;
    double h = 1 / n;
    double x0, v0, un, u0, vn, l = 1., m = 0, ind_max_razn = 0;
    x0 = 0;
    un = u0 = 0;
    v0 = p;
    for (int i = 0; i <= n; i++)
    {
        x0 = i * h;
        k0 = v0 + h * F(x0, l, v0);
        k1 = v0 + h * F(x0 + h / 2., l, v0 + h * k0 / 2.);
        k2 = v0 + h * F(x0 + h / 2., l, v0 + h * k1 / 2.);
        k3 = v0 + h * F(x0 + h, l, v0 + h * k2);
        un = u0 + (h / 6.) * (k0 + 2. * k1 + 2. * k2 + k3);
        vn = k0;
        if (abs(un - True_Answer(i * h)) > m)
        {
            m = abs(un - True_Answer(i * h));
            ind_max_razn = i;
        }
        cout << x0 << " " << u0 << endl;
        u0 = un;
        v0 = vn;
        
    }

    cout << "Max error is: " << m << " X is: " << ind_max_razn * h << endl;
    cout << "Parameter is: " << p << endl;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
