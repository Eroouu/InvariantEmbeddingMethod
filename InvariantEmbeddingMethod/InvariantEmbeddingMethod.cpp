// InvariantEmbeddingMethod.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
namespace functions1
{
    double r(double l)
    {
        return  1. / l;
    }
    double b(double z, double l, double temp_z)
    {
        if (abs(z - l) < 1e-5)
            return r(z);
        else
        {
            return b(z, l - temp_z, temp_z) * (1 - r(l - temp_z) * temp_z);
        }
    }
    double a(double z, double l, double temp_z)
    {
        if (abs(z - l) < 1e-5 && z != 0)
            return 1;
        else if (z == 0)
            return 0;
        else
        {

            return a(z, l - temp_z, temp_z) * (1 - r(l - temp_z) * temp_z);
        }
    }

    double s(double l)
    {
        return   1. / l;
    }
    double u(double z, double l, double temp_z)
    {
        if (abs(z - l) < 1e-5)
            return s(z);
        else
        {
            return u(z, l - temp_z, temp_z) + (-s(l - temp_z) * b(z, l - temp_z, temp_z) * temp_z);
        }
    }
    double y(double z, double l, double temp_z)
    {
        if (abs(z - l) < 1e-5 && z != 0)
            return 0;
        else if (z == 0)
            return 0;
        else
        {
            double w1 = y(z, l - temp_z, temp_z), w2 = -s(l - temp_z), w3 = a(z, l - temp_z, temp_z);
            return y(z, l - temp_z, temp_z) + (-s(l - temp_z) * a(z, l - temp_z, temp_z) * temp_z);
        }
    }
}
/// <summary>
/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// </summary>
namespace functions2
{
    double q = 1;
    double EI_x = 1;
    double temp_l = 0.1;

    double r(double l)
    {
        double temp;
        if (abs(l) <= 0.11)
            temp = 1. / l;
        else
            temp = r(l - temp_l) + (q / EI_x * (l - temp_l) * (l - temp_l) / 2 - r(l - temp_l) * r(l - temp_l)) * temp_l;
        return temp;
    }


    double b(double z, double l, double temp_z)
    {
        double temp;
        if (abs(z - l) < 1e-5)
            temp = r(z);
        else
        {
            temp = b(z, l - temp_z, temp_z) * (1 - r(l - temp_z) * temp_z);
        }
        return temp;
    }
    double a(double z, double l, double temp_z)
    {
        if (abs(z - l) < 1e-5 && abs(z) > 1e-5)
            return 1;
        else if (z == 0)
            return 0;
        else
        {

            return a(z, l - temp_z, temp_z) * (1. - r(l - temp_z) * temp_z);
        }
    }
    double s(double l)
    {
        double temp;
        if (abs(l) < 1e-5)
            return 0;
        else
        {
            double w1 = s(l - temp_l), w2 = r(l - temp_l);
            return s(l - temp_l) + (-s(l - temp_l) * r(l - temp_l)) * temp_l;
        }

    }
    double u(double z, double l, double temp_z)
    {
        double temp;
        if (abs(z - l) < 1e-5)
            temp = s(z);
        else
        {
            temp = u(z, l - temp_z, temp_z) + (-s(l - temp_z) * b(z, l - temp_z, temp_z) * temp_z);
        }
        return temp;
    }
    double y(double z, double l, double temp_z)
    {
        double temp;
        if (abs(z - l) < 1e-5 && z != 0)
            temp = 0;
        else if (z == 0)
            temp = 0;
        else
        {
            temp = y(z, l - temp_z, temp_z) + (-s(l - temp_z) * a(z, l - temp_z, temp_z) * temp_z);
        }
        return temp;
    }
}
/// <summary>
/// /////////////////////////////////////////////////////////////////////////
/// </summary>
/// <param name="V"></param>
namespace functions3
{
    double q = 1;
    double EI_x = 1;
    double temp_l = 1;

    double r(double l)
    {
        return 1. / (l);
    }

    double b(double z, double l, double temp_z)
    {
        double temp;
        if (abs(z - l) < 1e-5)
            temp = r(z);
        else
        {
            temp = b(z, l - temp_z, temp_z) * (1 - r(l - temp_z) * temp_z);
        }
        return temp;
    }
    double a(double z, double l, double temp_z)
    {
        if (abs(z - l) < 1e-5 && abs(z) > 1e-5)
            return 1;
        else if (z == 0)
            return 0;
        else
        {

            return a(z, l - temp_z, temp_z) * (1 - r(l - temp_z) * temp_z);
        }
    }

    double s(double l)
    {
        if (abs(l) < 1e-5)
            return 0.;
        else if (l <= 0.1)
            return l;
        else
            return 1. / l ;
    }
    double u(double z, double l, double temp_z)
    {
        double temp;
        if (abs(z - l) < 1e-5)
            temp = s(l);
        else
        {
            temp = u(z, l - temp_z, temp_z) + (-s(l - temp_z) * b(z, l - temp_z, temp_z) * temp_z);
        }
        return temp;
    }
    double y(double z, double l, double temp_z)
    {
        double temp;
        if (abs(z - l) < 1e-5 && z != 0)
            temp = 0;
        else if (z == 0)
            temp = 0;
        else
        {
            temp = 0;
            temp += y(z, l - temp_z, temp_z) + (-s(l - temp_z) * a(z, l - temp_z, temp_z) * temp_z);
        }
        return temp;
    }
}

/// <summary>
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// </summary>
/// <param name="V"></param>
void PrintVector(vector<double> V)
{
    cout << fixed << std::setprecision(5);
    cout << "-------------------------------------------------------------" << endl;
    for (int i = 0; i < V.size(); i++)
    {
        cout << setw(7) << V[i] << "  " << endl;
    }
    cout << "-------------------------------------------------------------" << endl;
}
using namespace functions3;
double Private_Solution(double z)
{
    return q * z * z * z * z / (24 * EI_x);
}
void Targetting_Method()
{

}
int main()
{
    vector<double> vect_a, vect_b, vect_y, vect_u;
    double l = 1, temp_z = 0.1;
    for (double i = 0.; i <= l; i += temp_z)
    {
        vect_a.push_back(y(i, l, temp_z));
        vect_b.push_back(u(i, l, temp_z));
    }
    vector<double> v_r;
    for (double  i = 0.1; i <= 1; i= i + 0.1)
    {
        v_r.push_back(y(0.1, i, 0.1));
        v_r.push_back(i);
    }
    cout << "vector y" << endl;
    PrintVector(vect_a);
    cout << y(0.1, 1, 0.1) <<  endl;
    cout << " ///////////////////" << endl;


    return 0;
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
