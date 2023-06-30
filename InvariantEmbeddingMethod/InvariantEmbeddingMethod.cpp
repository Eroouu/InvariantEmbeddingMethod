// InvariantEmbeddingMethod.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include "Base.h"
#include "Bridge.h"
#include "Plate.h"
#include "TargettingMethod.h"
#include <ctime>
#include "PlateX.h"
using namespace std;

void BridgeMethod(double q_con, double EI_x, double q,double l, double h)
{
    Bridge sol1(q_con, EI_x, q,l, h);
    sol1.set_all();
    vector<double> y = sol1.get_ans();
    double err = 0, x = 0;
    //sol1.debug();
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
void PlateMethod(double q_v, double lambda, double q, double l, double h)
{
    Plate sol1(q_v, lambda, q, l, h);
    sol1.set_all();
    vector<double> y = sol1.get_ans();
    double err = 0, x = 0;
    //sol1.debug();
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
    cout << "Error is: " << err << " h is: " << h << endl;
}
void PlateXMethod(double lambda, double q, double l, double h)
{
    PlateX sol1(0, lambda, q, l, h);
    sol1.set_all();
    vector<double> y = sol1.get_ans();
    double err = 0, x = 0;
    //sol1.debug();
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
    cout << "Error is: " << err << " h is: " << h << endl;
}
void TargetMethod(double q_con, double EI_x, double q, double l, double h)
{
    TargettingMethod sol(q_con, EI_x, l, h);
    double p = sol.FindP();
    double k0, k1, k2, k3;
    double x0, v0, un, u0, vn, m = 0, ind_max_razn = 0;
    x0 = 0;
    un = u0 = 0;
    v0 = p;
    for (int i = 0; i <= l/h+1; i++)
    {
        x0 = i * h;
        k0 = v0 + h * sol.F(x0, l, v0);
        k1 = v0 + h * sol.F(x0 + h / 2., l, v0 + h * k0 / 2.);
        k2 = v0 + h * sol.F(x0 + h / 2., l, v0 + h * k1 / 2.);
        k3 = v0 + h * sol.F(x0 + h, l, v0 + h * k2);
        un = u0 + (h / 6.) * (k0 + 2. * k1 + 2. * k2 + k3);
        vn = k0;
        if (abs(un - sol.TrueY(i * h)) > m)
        {
            m = abs(un - sol.TrueY(i * h));
            ind_max_razn = i;
        }
        //cout << x0 << " " << u0 << " " << abs(un - True_Answer(i * h)) <<  endl;
        u0 = un;
        v0 = vn;

    }
    cout << "Max error is: " << m << " X is: " << ind_max_razn * h << endl;
    cout << "Parameter is: " << p << "; h is " << h << endl;
}
int main()
{
    double h = 1e-2;
    double l = 1.;
    double q_con = 1.;
    double EI_x = 1.;
    double q_v = 200;
    double lambda = 20;
    double start_time1 = clock();
    //BridgeMethod(q_con, EI_x, 0, l,h);
    PlateMethod(q_v, lambda, 0, l, h);
    PlateXMethod(lambda, 0, l, h);
    double end_time1 = clock();
    cout << "runtime of InvEmbedding = " << (end_time1-start_time1) / 1000.0 << endl;
    //RungeMethod(1., 1., 0 ,l,h);
    double start_time2 = clock();
    TargetMethod(q_con, EI_x, 0, l, h);
    double end_time2 = clock();
   
    cout << "runtime of Targetting = " << (end_time2 - start_time2) / 1000.0 << endl;
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
