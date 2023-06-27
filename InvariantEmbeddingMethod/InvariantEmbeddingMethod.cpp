// InvariantEmbeddingMethod.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <vector>
#include <tuple>
#include <math.h>
using namespace std;

namespace m752
{
	const double l = 1;
	const double a1 = 1;
	const double a2 = 0;
	const double a3 = 1;
	const double a4 = 0;
	double a(double t)
	{
		return 0;
	}
	double b(double t)
	{
		return 1;
	}
	double c(double t)
	{
		return 0;
	}
	double d(double t)
	{
		return -1;
	}
	double f(double t)
	{
		return 1;
	}
}

using namespace m752;

int find_index(double l, double h)
{
	int i = 0;
	while (abs(i - l / h) > 1e-5 )
	{
		i++;
	}
	return i;
}

vector<vector<double>> vec_r_s(double h) // l is first, z is second
{
	vector<double> ans_r, ans_s;
	for (int i = 0; i < 1 / h + 1; i++)
	{
		if (i == 0)
		{
			ans_r.push_back(a2 / (a3 * a2 - a1 * a4));
			ans_s.push_back(a1 / (a1 * a4 - a2 * a3));
		}
		else
		{
			ans_r.push_back(ans_r[i - 1]  + dr(i * h, ans_r, ans_s));
			ans_s.push_back(ans_s[i - 1] + ds(i * h, ans_r, ans_s));
		}
			
	}
	vector<vector<double>> rez;
	rez.push_back(ans_r);
	rez.push_back(ans_s);
	return rez;
}
double dr(double t, vector<double> vec_r, vector<double> vec_s)
{
	double temps = vec_s[find_index(t, l)] , tempr = vec_s[find_index(t, l)];;
	return b(t) * temps + tempr * ( a(t) - a3 * b(t) * temps - a4 * d(t) * temps)
		- tempr * tempr * (a3 * a(t) + a4 * c(t));
}
double ds(double t, vector<double> vec_r, vector<double> vec_s)
{
	double temps = vec_s[find_index(t, l)], tempr = vec_s[find_index(t, l)];;
	return c(t) * tempr + temps * (d(t) - a3 * a(t) * tempr - a4 * c(t) * tempr)
		- temps * temps * (a3 * b(t) + a4 * d(t));
}

vector<vector<double>> vec_p(double h, vector<double> vec_r, vector<double> vec_s)
{
	vector<vector<double>> ans;
	for (int i = 0; i < 1 / h + 1; i++)
	{
		vector<double> temp;
		for (int j = 0; j <= i; j++)
		{
			if (i == j)
				temp.push_back(vec_r[find_index(i, l)]);
			else
				temp.push_back(ans[i-1][j] + h * dp(j, i, h, vec_r, vec_s) * ans[i - 1][j] );
		}
		ans.push_back(temp);
	}

	return ans;
}
double dp(int t, int T,double h,  vector<double> vec_r, vector<double> vec_s)
{
	double temps = vec_s[t], tempr = vec_r[t], th = t * h;
	return -( tempr * (a3 * a(t * h) + a4 * c(t * h)) 
		+ temps * (a3 * b(t * h) + a4 * d(t * h)) );
}
vector<vector<double>> vec_q(double h, vector<double> vec_r, vector<double> vec_s)
{
	vector<vector<double>> ans;
	for (int i = 0; i < 1 / h + 1; i++)
	{
		vector<double> temp;
		for (int j = 0; j <= i; j++)
		{
			if (i == j)
				temp.push_back(vec_s[find_index(i, l)]);
			else
				temp.push_back(ans[i - 1][j] + h * dq(j, i, h, vec_r, vec_s) * ans[i - 1][j]);
		}
		ans.push_back(temp);
	}

	return ans;
}
double dq(int t, int T, double h, vector<double> vec_r, vector<double> vec_s)
{
	double temps = vec_s[t], tempr = vec_r[t], th = t * h;
	return -(tempr * (a3 * a(t * h) + a4 * c(t * h))
		+ temps * (a3 * b(t * h) + a4 * d(t * h)));
}

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
			k1 = 1 - vec_s[i - 1] * (1 + r(l));
			k2 = 1 - (vec_s[i - 1] + h / 2 * k1) * (1 + r(l + h/2));
			k3 = 1 - (vec_s[i - 1] + h / 2 * k2) * (1 + r(l + h/2));
			k4 = 1 - (vec_s[i - 1] + h  * k3) * (1 + r(l + h));
			//vec_s.push_back(vec_s[i-1] + h*(k1 + 2*k2 + 2*k3 + k4) / 6);
			vec_s.push_back(vec_s[i - 1] + h * k1);
		}	
		l += h;
	}
	return vec_s;
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
			{
				/*double k1, k2, k3, k4;
				k1 = y_l(j * h, (i - 1) * h, h, s, a);
				k2 = y_l(j * h, (i - 1) * h, h, s, a);
				k3 = y_l(j * h, (i - 1) * h, h, s, a);
				k4 = y_l(j * h, (i - 1) * h, h, s, a);*/
				temp.push_back(ans[i - 1][j] + h * y_l(j*h, i*h - h, h, s,a));
			}
				
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
void tempOutput(vector<vector<double>> y1, vector<vector<double>> y2, double h)
{
	cout << "y1         y2\n";
	for (int i = 0; i < 1 / h + 1; i++)
	{
		cout << y1[y1.size() - 1][i] << "   " << y2[y2.size() - 1][2 * i] << endl;
	}
	cout << endl;
}
double ErrorCount(double h)
{
	double x = 0;
	double err = 0;
	vector<double> s1 = vec_s(h);
	vector<double> s2 = vec_s(h/2);
	vector < vector<double>> a1 = vec_a(h);
	vector < vector<double>> a2 = vec_a(h/2);
	vector<vector<double>> y1 = vec_y(h, s1, a1);
	vector<vector<double>> y2 = vec_y(h/2, s2, a2);
	vector<double> y;
	for (int i = 0; i < y1.size(); i++)
	{
		y.push_back(2 * y1[y1.size() - 1][i] - y2[y2.size() - 1][2 * i]);
	}
	//tempOutput(y1, y2, h);
	cout << "Y   TrueY  currErr\n";
	for (int i = 0; i < 1/h + 1; i++) 
	{
		double temp_otv = y[find_index(x, h)];
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
	double h = 0.05;
	double err =ErrorCount(h);
	cout << "Error is: " << err <<" h is: "<< h ;
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
