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
	const double a2 = 2;
	const double a3 = 1;
	const double a4 = 1.5;
	double a(double t)
	{
		return 1;
	}
	double b(double t)
	{
		return 1;
	}
	double c(double t)
	{
		return 1;
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
double dr(double t, double r, double s);
double ds(double t, double r, double s);

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
			ans_r.push_back(ans_r[i - 1] + h * dr((i - 1) * h, ans_r[i - 1], ans_s[i - 1]));
			//cout << dr(i - 1, h, ans_r, ans_s) << endl;
			ans_s.push_back(ans_s[i - 1] + h * ds((i - 1) * h, ans_r[i - 1], ans_s[i - 1]));
		}

	}
	vector<vector<double>> rez;
	rez.push_back(ans_r);
	rez.push_back(ans_s);
	return rez;
}
vector<vector<double>> RK(double h)
{
	int N = 2;
	double l = 1;
	double k1, k2, k3, k4,
		l1, l2, l3, l4;
	vector<double> r, s;
	vector<vector<double>> rs;
	r.push_back(a2 / (a3 * a2 - a1 * a4));
	s.push_back(-a1 / (a3 * a2 - a1 * a4));

	for (int i = 0; i < l / h + 1; i++)
	{
		k1 = dr(h * i, r[i], s[i]);
		l1 = ds(h * i, r[i], s[i]);
		k2 = dr(h * i + h / 2, r[i] + h * k1 / 2, s[i] + h * l1 / 2);
		l2 = ds(h * i + h / 2, r[i] + h * k1 / 2, s[i] + h * l1 / 2);
		k3 = dr(h * i + h / 2, r[i] + h * k2 / 2, s[i] + h * l2 / 2);
		l3 = ds(h * i + h / 2, r[i] + h * k2 / 2, s[i] + h * l2 / 2);
		k4 = dr(h * i + h, r[i] + h * k3, s[i] + h * l3);
		l4 = ds(h * i + h, r[i] + h * k3, s[i] + h * l3);

		r.push_back(r[i] + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6);
		s.push_back(s[i] + h * (l1 + 2 * l2 + 2 * l3 + l4) / 6);
	}
	rs.push_back(r);
	rs.push_back(s);
	return rs;
}

double dr(double t,  double r, double s)
{
	//cout << b(t) * s << " | " << r * (a(t) - a3 * b(t) * s - a4 * d(t) * s) << " | " << -r * r * (a3 * a(t) + a4 * c(t)) << endl;
	return b(t) * s
		+ r * (a(t) - a3 * b(t) * s - a4 * d(t) * s)
		- r * r * (a3 * a(t) + a4 * c(t));
}
double ds(double t, double r, double s)
{
	return c(t) * r 
		+ s * (d(t) - a3 * a(t) * r - a4 * c(t) * r)
		- s * s * (a3 * b(t) + a4 * d(t));
}
double dpq(int t, double h, double r, double s);

vector<vector<double>> vec_p(double h, vector<double> vec_r, vector<double> vec_s)
{
	vector<vector<double>> ans;
	for (int i = 0; i < 1 / h + 1; i++)
	{
		vector<double> temp;
		for (int j = 0; j <= i; j++)
		{
			if (i == j)
				temp.push_back(vec_r[i]);
			else
				temp.push_back(ans[i - 1][j] + h * dpq( i - 1, h, vec_r[i-1], vec_s[i-1]) * ans[i - 1][j]);
		}
		ans.push_back(temp);
	}

	return ans;
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
				temp.push_back(vec_s[i]);
			else
				temp.push_back(ans[i - 1][j] + h * dpq( i - 1, h, vec_r[i - 1], vec_s[i - 1]) * ans[i - 1][j]);
		}
		ans.push_back(temp);
	}

	return ans;
}
double dpq(int t, double h, double r, double s)
{
	double th = t * h;
	return -(r * (a3 * a(th) + a4 * c(th))
		+ s * (a3 * b(th) + a4 * d(th)));
}


vector<vector<double>> vec_m_n(double h, vector<double> vec_r, vector<double> vec_s)
{
	vector<vector<double>> ans_m_n;
	vector<double> n, m;
	for (int i = 0; i < 1 / h + 1; i++)
	{
		if (i == 0)
		{
			m.push_back(0);
			n.push_back(0);
		}
		else
		{
			double t = i - 1;
			double otr_part = m[t] * (a3 * a(t * h) + a4 * c(t * h)) + n[t] * (a3 * b(t * h) + a4 * d(t * h)) + f(t * h);
					
			m.push_back(m[t]+ h *(a(t * h) * m[t] + b(t * h) * n[t]- otr_part * vec_r[t]));

			n.push_back(n[t]+ h * (c(t * h) * m[t] + d(t * h) * n[t] + f(t * h) - otr_part * vec_s[t]));
				
		}
	}
	ans_m_n.push_back(m);
	ans_m_n.push_back(n);
	return ans_m_n;
}
vector<vector<double>> vec_u(double h, vector<double> m, vector<double> n, vector<vector<double>> p)
{
	vector<vector<double>> ans_u;
	for (int i = 0; i < 1 / h + 1; i++)
	{
		vector<double> temp;
		for (int j = 0; j <= i; j++)
		{
			if (i == j)
			{
				temp.push_back(m[i]);
			}
			else
			{
				double T = (i - 1) * h;
				double du = -(m[j] * (a3 * a(T) + a4 * c(T))+ n[j] * (a3 * b(T) + a4 * d(T)) + f(T)) * p[i - 1][j];
							
				temp.push_back(ans_u[i - 1][j] + h * du);
			}
		}
		ans_u.push_back(temp);
	}
	return ans_u;
}
vector<vector<double>> vec_v(double h, vector<double> m, vector<double> n, vector<vector<double>> q)
{
	vector<vector<double>> v;
	for (int i = 0; i < 1 / h + 1; i++)
	{
		vector<double> temp;
		for (int j = 0; j <= i; j++)
		{
			if (i == j)
			{
				temp.push_back(m[i]);
			}
			else
			{
				double T = (i - 1) * h;
				double dv = -(m[j] * (a3 * a(T) + a4 * c(T))+ n[j] * (a3 * b(T) + a4 * d(T)) + f(T)) * q[i - 1][j];
							
				temp.push_back(v[i - 1][j] + h * dv);
			}
		}
		v.push_back(temp);
	}
	return v;
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
void PrintMatrix(vector<vector<double>> matrix)
{
	cout << "--------------------------------------" << endl;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			cout << matrix[i][j] << "  ";
		}
		cout << endl;
	}
	cout << "--------------------------------------" << endl;
}
void PrintVector(vector<double> matrix)
{
	cout << "--------------------------------------" << endl;

	for (int i = 0; i < matrix.size(); i++)
	{
		cout << matrix[i] << "  ";
	}
	cout << endl;
	
	cout << "--------------------------------------" << endl;
}
double TrueAnswer(double t)
{
	return 2 * exp(2*t) / (5 * exp(2) - 3) - t/2 - (-9 + 5* exp(2))/ (5 * exp(2) - 3);
}
double ErrorCount(double h)
{
	double err = 0;
	//vector<vector<double>>  rs = vec_r_s(h);

	vector<double> r = RK(h)[0], s = RK(h)[1];

	//PrintVector(r);
	//PrintVector(s);

	vector< vector<double>> p = vec_p(h, r, s);
	vector< vector<double>> q = vec_q(h, r, s);

	vector<double> m = vec_m_n(h, r, s)[0], n = vec_m_n(h, r, s)[1];

	vector<vector<double>> u = vec_u(h, m, n, p);
	//vector<vector<double>> v = vec_v(h, m, n, q);
	
	//PrintMatrix(u);
	//PrintMatrix(p);
	
	vector<double> x;
	for (int i = 0; i < u[u.size() - 1].size(); i++)
	{
		x.push_back(u[u.size() - 1][i] + p[p.size() - 1][i]);
	}
	//PrintVector(x);
	double koord = 0;
	cout << "Y   TrueY  currErr\n";
	for (int i = 0; i < l / h + 1; i++)
	{
		double temp_otv = x[i];
		if (abs(temp_otv - TrueAnswer(koord))>err)
		{
			err = abs(temp_otv - TrueAnswer(koord));
		}
		cout << temp_otv << "  " << TrueAnswer(koord) << "  " << abs(temp_otv - TrueAnswer(koord)) << endl;
		koord += h;
	}
	/*
	double koord = 0;
	for (int i = 0; i < 1 / h + 1; i++)
	{
		cout << x[i] << "  " << endl;
		koord += h;
	}*/
	return err;
}
int main()
{
	//EilerMeth(0.01);
	double h = 0.01;
	cout << "---_---" << endl;
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
