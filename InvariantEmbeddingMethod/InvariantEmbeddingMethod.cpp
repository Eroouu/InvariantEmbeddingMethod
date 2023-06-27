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
	const double a2 = 1;
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
	while (abs(i - l / h) > 1e-5)
	{
		i++;
	}
	return i;
}
double dr(double i, double h, vector<double> vec_r, vector<double> vec_s);
double ds(double i, double h, vector<double> vec_r, vector<double> vec_s);

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
			ans_r.push_back(ans_r[i - 1] + h * dr(i - 1, h, ans_r, ans_s));
			ans_s.push_back(ans_s[i - 1] + h * ds(i - 1, h, ans_r, ans_s));
		}

	}
	vector<vector<double>> rez;
	rez.push_back(ans_r);
	rez.push_back(ans_s);
	return rez;
}
double dr(double i, double h,  vector<double> vec_r, vector<double> vec_s)
{
	double temps = vec_s[i], tempr = vec_r[i], t = i * h;
	return b(t) * temps + tempr * (a(t) - a3 * b(t) * temps - a4 * d(t) * temps)
		- tempr * tempr * (a3 * a(t) + a4 * c(t));
}
double ds(double i, double h, vector<double> vec_r, vector<double> vec_s)
{
	double temps = vec_s[i], tempr = vec_r[i],t = i * h;
	return c(t) * tempr + temps * (d(t) - a3 * a(t) * tempr - a4 * c(t) * tempr)
		- temps * temps * (a3 * b(t) + a4 * d(t));
}
double dp(int t, int T, double h, vector<double> vec_r, vector<double> vec_s);
double dq(int t, int T, double h, vector<double> vec_r, vector<double> vec_s);
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
				temp.push_back(ans[i - 1][j] + h * dp(j, i, h, vec_r, vec_s) * ans[i - 1][j]);
		}
		ans.push_back(temp);
	}

	return ans;
}
double dp(int t, int T, double h, vector<double> vec_r, vector<double> vec_s)
{
	double temps = vec_s[t], tempr = vec_r[t], th = t * h;
	return -(tempr * (a3 * a(t * h) + a4 * c(t * h))
		+ temps * (a3 * b(t * h) + a4 * d(t * h)));
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

vector<vector<double>> vec_m_n(double h, vector<double> vec_r, vector<double> vec_s)
{
	vector<vector<double>> ans_m_n;
	vector<double> temp_n, temp_m;
	for (int i = 0; i < 1 / h + 1; i++)
	{
		if (i == 0)
		{
			temp_m.push_back(0);
			temp_n.push_back(0);
		}
		else
		{
			double otr_part = temp_m[i - 1] * (a3 * a(i * h) + a4 * c(i * h)) +
				temp_n[i - 1] * (a3 * b(i * h) + a4 * d(i * h))
				+ f(i * h);
			temp_m.push_back(temp_m[i - 1]
				+ h *
				(
					a(i * h) * temp_m[i - 1] + b(i * h) * temp_n[i - 1]
					- otr_part * vec_r[i]
					)
				* temp_m[i - 1]);
			temp_n.push_back(temp_n[i - 1]
				+ h *
				(
					c(i * h) * temp_m[i - 1] + d(i * h) * temp_n[i - 1] + f(i * h)
					- otr_part * vec_s[i]
					)
				* temp_m[i - 1]);
		}
	}
	ans_m_n.push_back(temp_m);
	ans_m_n.push_back(temp_n);
	return ans_m_n;
}
vector<vector<double>> vec_u(double h, vector<double> vec_m, vector<double> vec_n, vector<vector<double>> vec_p)
{
	vector<vector<double>> ans_u;
	for (int i = 0; i < 1 / h + 1; i++)
	{
		vector<double> temp;
		for (int j = 0; j <= i; j++)
		{
			if (i == j)
			{
				temp.push_back(vec_m[i]);
			}
			else
			{
				double T = (i - 1) * h;
				double du = -(vec_m[j] * (a3 * a(T) + a4 * c(T))
					+ vec_n[j] * (a3 * b(T) + a4 * d(T)) + f(T)) * vec_p[i - 1][j];
				temp.push_back(ans_u[i - 1][j] + h * du);
			}
		}
		ans_u.push_back(temp);
	}
	return ans_u;
}
vector<vector<double>> vec_v(double h, vector<double> vec_m, vector<double> vec_n, vector<vector<double>> vec_q)
{
	vector<vector<double>> ans_v;
	for (int i = 0; i < 1 / h + 1; i++)
	{
		vector<double> temp;
		for (int j = 0; j <= i; j++)
		{
			if (i == j)
			{
				temp.push_back(vec_m[i]);
			}
			else
			{
				double T = (i - 1) * h;
				double dv = -(vec_m[j] * (a3 * a(T) + a4 * c(T))
					+ vec_n[j] * (a3 * b(T) + a4 * d(T)) + f(T)) * vec_q[i - 1][j];
				temp.push_back(ans_v[i - 1][j] + h * dv);
			}
		}
		ans_v.push_back(temp);
	}
	return ans_v;
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
	double err = 0;
	vector<vector<double>>  rs = vec_r_s(h);
	vector<double> r = rs[0], s = rs[1];
	vector< vector<double>> p = vec_p(h, r, s);
	vector< vector<double>> q = vec_q(h, r, s);
	vector< vector<double>> mn = vec_m_n(h, r, s);
	vector<double> m = mn[0], n = mn[1];
	vector<vector<double>> u = vec_u(h, m, n, p);
	vector<vector<double>> v = vec_v(h, m, n, q);

	vector<double> x;
	for (int i = 0; i < u[u.size() - 1].size(); i++)
	{
		x.push_back(u[u.size() - 1][i] + p[p.size() - 1][i]);
	}

	cout << "Y   TrueY  currErr\n";
	/*for (int i = 0; i < 1 / h + 1; i++)
	{
		double temp_otv = y[find_index(x, h)];
		if (abs(temp_otv - RightAns(x))>err)
		{
			err = abs(temp_otv - RightAns(x));
		}
		cout << temp_otv << "  " << RightAns(x) << "  " << abs(temp_otv - RightAns(x)) << endl;
		x += h;
	}*/
	double koord = 0;
	for (int i = 0; i < 1 / h + 1; i++)
	{
		cout << x[i] << "  " << endl;
		koord += h;
	}
	return err;
}
int main()
{
	//EilerMeth(0.01);
	double h = 0.1;
	cout << " Maksim lox " << endl;
	double err = ErrorCount(h);
	cout << "Error is: " << err << " h is: " << h;
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
