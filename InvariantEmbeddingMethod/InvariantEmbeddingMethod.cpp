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

vector<vector<double>> vec_r(double h) // Inverted array of all a_i of (array of elements where we find one r(a+h,c_j) for all c_j)
{
	vector<vector<double>> ans;
	double a = 1, c = 1;
	for (int i = 0; i < 1 / h + 1; i++)
	{
		vector<double> temp;
		for (int j = 0; j < 1 / h + 1; j++)
		{
			temp.push_back(c + h * g(c, 0, a));
			c -= h;
		}
		ans.push_back(temp);
		a -= h;
	}
	return ans;
}
double r(double a, double c,double delta, vector<vector<double>> r_c)
{
	return r(a + delta, c + r(a + delta, c, delta) * delta, delta) - delta * g(c, r(a, c, delta), a);
}
double RightAns(double x)
{
	double ans = -2 * exp(-x) / (exp(1) + exp(-1)) + 2 * exp(x) / (exp(1) + exp(-1)) - 2 * x;
	return ans;
}
vector<double> EilerMeth(double h);
double ErrorCount()
{
	double h = 0.01;
	vector<double> y = EilerMeth(h);
	double x = 0;
	double err = 0;
	cout << "Y   TrueY  currErr\n";
	for (int i = 0; i < y.size(); i++) 
	{
		if (abs(y[i]-RightAns(x))>err)
		{
			err = abs(y[i] - RightAns(x));
		}
		cout << y[i] << "  " << RightAns(x) << "  " << abs(y[i] - RightAns(x)) << endl;
		x += h;
	}
	return err;
}
void Outcmd(vector<double> y, vector<double> u, double h);
vector<double> EilerMeth(double h)
{
	vector<double> y, u;
	double delta = 0.1;
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
	//Outcmd(y, u, h);
	return y;
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
