// InEmM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <ctime>
using namespace std;

double q = 1.;
double EI_x = 1.;
double temp_l = 1.;
double F(double z, double l, double v)
{
    return (q * l * z / 2. - q * z * z / 2.) / EI_x + v;
}

double True_Answer(double x)
{
    return -(1. / 24) * q * x * x * x * x / EI_x + (1. / 12) * q * x * x * x / EI_x - (1. / 24) * q * x / EI_x;;
}

const double a1 = 1;
const double a2 = 1;
const double a3 = 1;
const double a4 = 0;
double a(double t)
{
    return 1;
}
double b(double t)
{
    return 1;
}
double c(double t)
{
    return 0;
}
double d(double t)
{
    return -1;
}

double f(double t)
{
    return 1;
}
double f1(double t, double r, double s)
{
    return s - r * s - r * r;
    //b(t) * s + r * (a(t) - a3 * b(t) * s - a4 * d(t) * s) - r * r * (a3 * a(t) + a4 * c(t));
}
double f2(double t, double r, double s)
{
    return s * s;
        //c(t) * r + s * (d(t) - a3 * a(t) * r - a4 * c(t) * r) - s * s * (a3 * b(t) + a4 * d(t));
}

vector<vector<double>> RK(double l)
{
    int N = 2;
    double h = 0.05;
    double k1, k2, k3, k4,
        l1, l2, l3, l4;
    vector<double> r, s;
    vector<vector<double>> rs;
    r.push_back(a2 / (a3 * a2 - a1 * a4));
    s.push_back(- a1 / (a3 * a2 - a1 * a4));

    for (int i = 0; i < l / h + 1; i++)
    {
        k1 = f1(h * i, r[i], s[i]);
        l1 = f2(h * i, r[i], s[i]);
        k2 = f1(h * i + h / 2, r[i] + h * k1 / 2, s[i] + h * l1 / 2);
        l2 = f2(h * i + h / 2, r[i] + h * k1 / 2, s[i] + h * l1 / 2);
        k3 = f1(h * i + h / 2, r[i] + h * k2 / 2, s[i] + h * l2 / 2);
        l3 = f2(h * i + h / 2, r[i] + h * k2 / 2, s[i] + h * l2 / 2);
        k4 = f1(h * i + h, r[i] + h * k3, s[i] + h * l3);
        l4 = f2(h * i + h, r[i] + h * k3, s[i] + h * l3);

        r.push_back(r[i] + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6);
        s.push_back(s[i] + h * (l1 + 2 * l2 + 2 * l3 + l4) / 6);
    }
    rs.push_back(r);
    rs.push_back(s);
    return rs;
}




int main()
{
    double l = 1;
    double h = 0.05;
    vector<vector<double>> rs = RK(l);
    for (int i = 0; i < l / h + 1; i++)
    {
        cout << rs[0][i] << "\t" << rs[1][i] <<endl;
    }
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
