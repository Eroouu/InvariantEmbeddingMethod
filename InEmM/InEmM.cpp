// InEmM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
using namespace std;

double q = 1.;
double EI_x = 1.;
double temp_l = 1.;
double F(double z, double l, double v)
{
    return (q * l * z / 2. - q * z * z / 2.) / EI_x + v;

}

double RuK(double l, double p)
{
    double n = 1e5;
    double k0, k1, k2, k3;
    double h = l / n;
    double x0; double v0; double un; double u0;
    x0 = 0;
    un = u0 = 0;
    v0 = p;
    k0 = v0 + h * F(x0, l, v0);
    for (int i = 0; i < n; i++)
    {
        x0 = i * h;
        u0 = un;
        v0 = k0;
        k0 = v0 + h * F(x0, l, v0);
        k1 = v0 + h * F(x0 + h / 2., l, v0 + h * k0 / 2.);
        k2 = v0 + h * F(x0 + h / 2., l, v0 + h * k0 / 2.);
        k3 = v0 + h * F(x0 + h, l, v0 + h * k2);
        un = u0 + (h / 6.) * (k0 + 2. * k1 + 2. * k2 + k3);
        
    }

    return un;
}

double Targetting_Method(double l)
{
    double p1 = 0, p2 = -10;
    double p;
    while (abs(RuK(l, p1)) > 1e-10)
    {
        p = (p2 + p1) / 2.;
        if (RuK(l, p1) * RuK(l, p) < 0)
            p2 = p;
        else if (RuK(l, p) * RuK(l, p2) < 0)
            p1 = p;
    }
    cout << "p is: " << p1 << endl;
    return p1;
}

double FF(double x)
{
    return -pow(x, 4) / 24 + pow(x, 3) / 12 - x / 24;
}

int main()
{
    int k;
    double p = Targetting_Method(1.);
    double k0, k1, k2, k3;
    double n = 1e4;
    double h = 1 / n;
    double x0, v0, un, u0;
    x0 = 0;
    un = u0 = 0;
    v0 = p;
    k0 = v0 + h * F(x0, 1., v0);
    double m = 0;
    for (int i = 0; i <= n; i++)
    {
       // cout << i * h << ' ' << un << ' ' << abs(un - FF(i * h)) << endl;
        if (m < abs(un - FF(i * h))) {
            m = abs(un - FF(i * h));
            k = i;
        }
        x0 = i * h;
        u0 = un;
        v0 = k0;
        k0 = v0 + h * F(x0, 1., v0);
        k1 = v0 + h * F(x0 + h / 2., 1., v0 + h * k0 / 2.);
        k2 = v0 + h * F(x0 + h / 2., 1., v0 + h * k1 / 2.);
        k3 = v0 + h * F(x0 + h, 1., v0 + h * k2);
        un = u0 + (h / 6.) * (k0 + .2 * k1 + 2. * k2 + k3);
    }

    cout << "Max error is: " << m << " X is: " << k * h << endl;
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
