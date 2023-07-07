// InvariantEmbeddingMethod.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <vector>
using namespace std;
namespace m751
{
	double f(double u,double v,double t)
	{
		return 1;
	}
	double g(double u, double v, double t)
	{
		return 1;
	}
	double c = 1; // значение на правом краю
	double T = 1;
	double h = 0.05; // шаги Т
	double delta = 0.05; // шаги С
}
using namespace m751;
vector<double> vec_r()
{
	vector<double> rt;
	vector<vector<double>> r;
	for (int i = 0; i < T / h + 1; i++) // шаги по T
	{
		vector<double> dc;
		for (int j = 0; j < T/h+1-i; j++) // шаги по C
		{
			if (i == 0)
			{
				dc.push_back(0);
			}
			else
			{
				double temp = r[i - 1][j] + h * (f(r[i - 1][j], j * h, (i - 1) * h) - g(r[i - 1][j], j * h, (i - 1) * h)
					* (r[i - 1][j + 1] - r[i - 1][j]) / delta);
				dc.push_back(temp);
			}
		}
		r.push_back(dc);
	}
	for (int i = 0; i < T / h + 1; i++)
	{
		rt.push_back(r[i][0]);
	}
	return rt;
}
vector<double> vec_u()
{
	return { 0 };
}

int main()
{
	vector<double> r=vec_r();
	for (int i = 0; i < T / h + 1; i++)
	{
		cout << r[i] << endl;
	}
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
