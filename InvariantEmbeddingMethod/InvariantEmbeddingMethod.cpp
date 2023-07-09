// InvariantEmbeddingMethod.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <vector>
using namespace std;
namespace m1141
{
	double f(double u,double v,double t)
	{
		return v;
	}
	double g(double u, double v, double t)
	{
		return (1-t*t)*u+exp(-t);
	}
	double c = 3; // значение на правом краю
	double T = 1;
	double h = 0.05; // шаги Т
	double delta = 0.05; // шаги С
}
using namespace m1141;
vector<vector<double>> vec_r()
{
	
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
				double temp = r[i - 1][j] + h * (f(r[i - 1][j], c + j * h, (i - 1) * h) 
					- g(r[i - 1][j], c + j * h, (i - 1) * h) * (r[i - 1][j + 1] - r[i - 1][j]) / delta);
				dc.push_back(temp);
			}
		}
		r.push_back(dc);
	}
	return r;
}
vector<vector<vector<double>>> vec_v(vector<vector<double>> r)
{
	vector<vector<vector<double>>> v;
	for (int i = 0; i < T / h + 1; i++) // шаги по T
	{
		vector<vector<double>> dc;
		for (int j = 0; j < i+1; j++) // шаги по t
		{
			vector<double> dt;
			for (int k = 0; k < T/h+1-i; k++) // шаги по C
			{
				if (j==i)
				{
					dt.push_back(c);
				}
				else
				{
					double temp;
					temp = v[i-1][j][k] + h * (g(r[i-1][k], c + k * delta, j * h)
						* (v[i-1][j][k+1] - v[i-1][j][k]) / delta);
					dt.push_back(temp);
				}
			}
			dc.push_back(dt);
		}
		v.push_back(dc);
	}
	return v;
}
vector<vector<vector<double>>> vec_u(vector<vector<double>> r)
{
	vector<vector<vector<double>>> u;
	for (int i = 0; i < T / h + 1; i++) // шаги по T
	{
		vector<vector<double>> dc;
		for (int j = 0; j < i + 1; j++) // шаги по t
		{
			vector<double> dt;
			for (int k = 0; k < T / h + 1 - i; k++) // шаги по C
			{
				if (j == i)
				{
					dt.push_back(r[k][i]);
				}
				else
				{
					double temp;
					temp = u[i - 1][j][k] + h * (g(r[i - 1][k], c + k * delta, j * h)
						* (u[i - 1][j][k + 1] - u[i - 1][j][k]) / delta);
					dt.push_back(temp);
				}
			}
			dc.push_back(dt);
		}
		u.push_back(dc);
	}
	return u;
}

int main()
{
	vector<vector<double>> r=vec_r();
	vector<vector<vector<double>>> v = vec_v(r);
	vector<vector<vector<double>>> u = vec_u(r);
	for (int i = 0; i < T / h + 1; i++) // шаги по T
	{
		for (int j = 0; j < i + 1; j++) // шаги по t
		{
			for (int k = 0; k < T / h + 1 - i; k++) // шаги по C
			{
				cout << u[i][j][k] << endl;
			}
		}
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
