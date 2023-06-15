// InvariantEmbeddingMethod.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <vector>
#include <tuple>
using namespace std;
namespace m752
{
	double f(double u)
	{
		return u;
	}
	double g(double x,double u, double l) // возможен 3й аргумент
	{
		return 1 - u;
	}

}
using namespace m752;
double r(double l)
{
	return (exp(2 * l) + 1) / (exp(2 * l) - 1);
}

double RightAns(double x)
{
	double ans = (-exp(1) * x + x - exp(1 - x) + exp(1)) / (1 - exp(1));
	return ans;
}

void Outcmd(vector<double> y, vector<double> u, double h);
double b_l(double z, double l, double h);
double a_l(double z, double l, double h);
double u_l(double z, double l, double h);
double y_l(double z, double l, double h);
double ds(double l, double h);

double a(double z, double l, double h)
{
	if (abs(z) <= 1e-5)
		return 0;
	else if (abs(z - l) <= 1e-5)
		return 1;
	else
		return a(z, l - h, h) + h * a_l(z, l - h, h);
}
double b(double z, double l, double h)
{
	if (abs(z - l) <= 1e-5)
		return r(l);
	else
		return b(z, l - h, h) + h * b_l(z , l - h, h);
}
double b_l(double z, double l, double h)
{
	return -r(l) * b(z, l, h);
}
double a_l(double z, double l, double h)
{
	return -r(l) * a(z, l, h);
}

double s(double l, double h)
{
	if (abs(l) <= 1e-5)
		return 0;
	else
		return s(l - h, h) + h * ds(l-h,h);
}
double ds(double l, double h)
{
	return 1 - s(l,h) - s(l,h) * r(l);
}

double y(double z, double l, double h)
{
	if (abs(z) <= 1e-5)
		return 0;
	else if (abs(z - l) <= 1e-5)
		return 0;
	else
		return y(z, l - h, h) + h * y_l(z, l - h, h);
}
double u(double z, double l, double h)
{
	if (abs(z - l) <= 1e-5)
		return s(l,h);
	else
		return u(z, l - h, h) + h * u_l(z, l - h, h);
}
double u_l(double z, double l, double h)
{
	return -s(l,h) * b(z, l, h);
}
double y_l(double z, double l, double h)
{
	return -s(l,h) * a(z, l, h);
}
double ErrorCount()
{
	double h = 0.05;
	double x = 0;
	double err = 0;
	cout << "Y   TrueY  currErr\n";
	for (int i = 0; i < 1/h + 1; i++) 
	{
		if (abs(y(x, 1, h)-RightAns(x))>err)
		{
			err = abs(y(x, 1, h) - RightAns(x));
		}
		cout << y(x, 1, h) << "  " << RightAns(x) << "  " << abs(y(x, 1, h) - RightAns(x)) << endl;
		x += h;
	}
	return err;
}
void Outcmd(vector<double> y, vector<double> u,double h)
{
	cout << "table of contents: x u y columns\n";
	double tempX = 0;
	for (int i = 0; i < y.size(); i++)
	{
		double  tempY, tempU;
		tempY = y[i];
		tempU = u[i];
		cout << tempX << " " << tempU << " " << tempY << endl;
		tempX += h;
	}
}
int main()
{
	//EilerMeth(0.01);
	double err =ErrorCount();
	cout << "Error is: " << err;
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
