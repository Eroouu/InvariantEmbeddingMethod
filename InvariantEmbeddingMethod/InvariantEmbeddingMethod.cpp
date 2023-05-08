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
        if (z == l)
            return r(z);
        else
        {         
            return b(z, l - temp_z, temp_z) * (1 - r(l - temp_z) * temp_z);
        }
    }
    double a(double z, double l, double temp_z)
    {
        if (z == l && z != 0)
            return 1;
        else if (z == 0)
            return 0;
        else
        {
         
            return a(z, l - temp_z, temp_z) * (1 - r(l - temp_z) * temp_z);
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
    vector<double> vect_a, vect_b;
    double l = 1, temp_z = 0.01;
    for (double i = 0.01; i <= l; i += temp_z)
    {
        vect_a.push_back( a(i, l, temp_z));
        vect_b.push_back( b(i, l, temp_z));
    }
    PrintVector(vect_a);
    PrintVector(vect_b);
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
