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
        if ( abs(z - l) < 1e-5 && z != 0)
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
        return   1./l;
    }
    double u(double z, double l, double temp_z)
    {
        if (abs(z - l) < 1e-5)
            return s(z);
        else
        {
            return u(z, l - temp_z, temp_z) + (- s(l - temp_z) * b(z, l - temp_z, temp_z) * temp_z);
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
            return y(z, l - temp_z, temp_z) + (-s(l - temp_z) * a(z, l - temp_z, temp_z) * temp_z);
        }
    }
}
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
using namespace functions1;
int main()
{
    vector<double> vect_a, vect_b, vect_y, vect_u;
    double l = 1, temp_z = 0.02;
    for (double i = 0.02; i <= l; i += temp_z)
    {
        //vect_a.push_back( a(i, l, temp_z));
        //vect_b.push_back( b(i, l, temp_z));
        vect_y.push_back(a(i, l, temp_z));
        vect_u.push_back(b(i, l, temp_z));
    }
    PrintVector(vect_y);
    PrintVector(vect_u);
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
