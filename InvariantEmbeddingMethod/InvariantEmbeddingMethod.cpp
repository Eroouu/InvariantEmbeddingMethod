// InvariantEmbeddingMethod.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include "BuildingEq.h"
#include <ctime>
using namespace std;

void ClassicMethod(double q_con, double EI_x, double q,double l, double h)
{
    BuildingEq sol1(q_con, EI_x, q,l, h);
    sol1.set_all();
    vector<double> y = sol1.get_ans();
    double err = 0, x = 0;
    cout << "Y   TrueY  currErr\n";
    for (int i = 0; i < l / h + 1; i++)
    {
        double temp_otv = y[i];
        if (abs(temp_otv - sol1.TrueY(x)) > err)
        {
            err = abs(temp_otv - sol1.TrueY(x));
        }
        cout << temp_otv << "  " << sol1.TrueY(x) << "  " << abs(temp_otv - sol1.TrueY(x)) << endl;
        x += h;
    }
    cout << "Error is: " << err << " h is: " << h<< endl;
}
void RungeMethod(double q_con, double EI_x, double q,double l, double h)
{
    BuildingEq sol1(q_con, EI_x, q,l, h);
    sol1.set_s();
    sol1.set_a();
    sol1.set_y();
    vector<vector<double>> y1 = sol1.get_y();
    BuildingEq sol2(q_con, EI_x, q, l, h/2);
    sol2.set_s();
    sol2.set_a();
    sol2.set_y();
    vector<vector<double>> y2 = sol2.get_y();
    vector<double> y;
    for (int i = 0; i < y1.size(); i++)
    {
        y.push_back(2 * y1[y1.size() - 1][i] - y2[y2.size() - 1][2 * i]);
    }
    double err = 0,x=0;
    cout << "Y   TrueY  currErr\n";
    for (int i = 0; i < 1 / h + 1; i++)
    {
        double temp_otv = y[i];
        if (abs(temp_otv - sol1.TrueY(x)) > err)
        {
            err = abs(temp_otv - sol1.TrueY(x));
        }
        cout << temp_otv << "  " << sol1.TrueY(x) << "  " << abs(temp_otv - sol1.TrueY(x)) << endl;
        x += h;
    }
    cout << "Error is: " << err << " h is: " << h<< endl;
}
int main()
{
    double h = 0.1;
    double l = 100.;
    double q_con = 0.01;
    double EI_x = 10000.;
    ClassicMethod(q_con, EI_x, 0, l,h);
    //RungeMethod(1., 1., 0 ,l,h);
    cout << "runtime = " << clock() / 1000.0 << endl;
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
