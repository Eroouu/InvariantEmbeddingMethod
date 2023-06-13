// InvariantEmbeddingMethod.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <vector>
#include <tuple>
using namespace std;
namespace m751
{
	double f(double u)
	{
		return u;
	}
	double g(double y,double r, double x) // возможен 3й аргумент
	{
		return y + 2 * x;
	}
	double a = 0, c = 0;
}
using namespace m751;
double r(double a, double c,double delta)
{
	if (a == 0)
		return 0;
	else
		return r(a + delta, c + r(a + delta, c, delta) * delta, delta) - delta * g(c, r(a, c, delta), a);
}
void Outcmd(vector<double> y, vector<double> u, double h);
void EilerMeth(double h)
{
	vector<double> y, u;
	double delta = -0.1;
	double x = 0;
	y.push_back(c);
	u.push_back(r(a, c, delta));
	while (x <= 1)
	{
		double tempY, tempU;
		double Yn, Un;
		Yn = y[y.size() - 1];
		Un = u[u.size() - 1];
		tempY = Yn + h * f(Un);
		tempU = Un + h * g(Yn, 0, x);
		x += h;
		y.push_back(tempY);
		u.push_back(tempU);
	}
	Outcmd(y, u, h);
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
	EilerMeth(0.01);
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
