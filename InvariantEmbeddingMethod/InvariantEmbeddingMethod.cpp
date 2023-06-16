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

double b_l(double z, double l, double h);
double u_l(double z, double l, double h, vector<double> s);
double y_l(double z, double l, double h, vector<double> s, vector<vector<double>> a);

vector<vector<double>> vec_a(double h) // l is first, z is second
{
	vector<vector<double>> ans;
	for (int i = 0; i < 1 / h + 1; i++)
	{
		vector<double> temp;
		for (int j = 0; j < i + 1; j++)
		{
			if (j == 0)
				temp.push_back(0);
			else if (j == i)
				temp.push_back(1);
			else
				temp.push_back(ans[i - 1][j] + h *(-r(i*h)*ans[i-1][j]));
		}
		ans.push_back(temp);
	}
	return ans;
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

vector<double> vec_s(double h)
{
	vector<double> vec_s;
	double l = 0;
	for (int i = 0; i < 1 / h + 1; i++)
	{
		if (i==0)
			vec_s.push_back(0);
		else
		{
			double k1, k2, k3, k4;
			k1 = 1 - vec_s[i - 1] * (1 - r(l));
			k2 = 1 - (vec_s[i - 1] + h/2 * k1) * (1 - r(l + h/2));
			k3 = 1 - (vec_s[i - 1] + h / 2 * k2) * (1 - r(l + h / 2));
			k4 = 1 - (vec_s[i - 1] + h  * k3) * (1 - r(l + h));
			vec_s.push_back(vec_s[i-1] + h*(k1 + 2*k2 + 2*k3 + k4) / 6);
		}	
		l += h;
	}
	return vec_s;
}
int find_index(double l, double h)
{
	int i = 0;
	while (abs(i - l / h) > 1e-5 )
	{
		i++;
	}
	return i;
}
vector<vector<double>> vec_y(double h, vector<double> s,vector<vector<double>> a) // l first ind, z is second
{
	vector<vector<double>> ans;
	for (int i = 0; i < 1 / h + 1; i++) // для определенного значения l 
	{
		vector<double> temp;
		for (int j = 0; j < i + 1; j++) // для x меньшего чем l
		{
			if (j == 0)
				temp.push_back(0);
			else if (j == i)
				temp.push_back(0);
			else
				temp.push_back(ans[i - 1][j] + h * y_l(j*h, i*h - h, h, s,a));
		}
		ans.push_back(temp);
	}
	return ans;
}
double u(double z, double l, double h, vector<double> s)
{
	if (abs(z - l) <= 1e-5)
		return s[find_index(l, h)];
	else
		return u(z, l - h, h,s) + h * u_l(z, l - h, h,s);
}
double u_l(double z, double l, double h, vector<double> s)
{
	return -s[find_index(l,h)] * b(z, l, h);
}
double y_l(double z, double l, double h, vector<double> s, vector<vector<double>> a)
{
	return -s[find_index(l,h)] * a[find_index(l,h)][find_index(z,h)];
}
double ErrorCount()
{
	double h = 0.05;
	double x = 0;
	double err = 0;
	vector<double> s = vec_s(h);
	vector < vector<double>> a = vec_a(h);
	vector<  vector<double>> y = vec_y(h, s, a);
	cout << "Y   TrueY  currErr\n";
	for (int i = 0; i < 1/h + 1; i++) 
	{
		double temp_otv = y[y.size() - 1][find_index(x, h)];
		if (abs(temp_otv - RightAns(x))>err)
		{
			err = abs(temp_otv - RightAns(x));
		}
		cout << temp_otv << "  " << RightAns(x) << "  " << abs(temp_otv - RightAns(x)) << endl;
		x += h;
	}
	return err;
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
