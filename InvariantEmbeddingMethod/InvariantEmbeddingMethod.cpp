﻿// InvariantEmbeddingMethod.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
/*
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
}*/
vector<vector<double>> vec_b(double h) // l is first, z is second
{
	vector<vector<double>> ans;
	for (int i = 0; i < 1 / h + 1; i++)
	{
		vector<double> temp;
		for (int j = 0; j <= i ; j++)
		{
			if(j == 0)
				temp.push_back(5.15);
			else if (j == i)
				temp.push_back(r(i * h));
			else
				temp.push_back(ans[i - 1][j] + h * (-r(i * h - h) * ans[i - 1][j]));
		}
		ans.push_back(temp);
	}
	return ans;
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
int find_index(double l, double h)
{
	int i = 0;
	while (abs(i - l / h) > 1e-5 )
	{
		i++;
	}
	return i;
}
vector<vector<double>> vec_u(double h, vector<double> s, vector<vector<double>> b) // l first ind, z is second
{
	vector<vector<double>> ans;
	for (int i = 0; i < 1 / h + 1; i++) // для определенного значения l 
	{
		vector<double> temp;
		for (int j = 0; j <= i; j++) // для x меньшего чем l
		{
			if (j == i)
				temp.push_back(s[i]);
			else
				temp.push_back(ans[i - 1][j] - h * s[i - 1] * b[i - 1][j] );
		}
		ans.push_back(temp);
	}
	return ans;
}
vector<vector<double>> vec_y(double h, vector<double> s,vector<vector<double>> u) // l first ind, z is second
{
	vector<vector<double>> ans;
	for (int i = 0; i < 1 / h + 1; i++) // для определенного значения l 
	{
		vector<double> temp;
		for (int j = 0; j <= i; j++) // для x меньшего чем l
		{
			if (j == i || j == 0)
				temp.push_back(0);
			else
				temp.push_back(temp[j - 1] + h * u[i][j - 1]);
		}
		ans.push_back(temp);
	}
	return ans;
}
void PrintMatrix(vector<vector<double>> matrix)
{
	cout << " -------------------------------" << endl;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << " -------------------------------" << endl;
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
	vector<double> s = vec_s(h);
	vector<vector<double>> b = vec_b(h);
	vector<vector<double>> u = vec_u(h, s, b);
	vector<vector<double>> y = vec_y(h, s, u);
	//PrintMatrix(b);
	cout << "Y   TrueY  currErr\n";
	for (int i = 0; i < 1/h + 1; i++) 
	{
		double temp_otv = y[y.size() - 1][i];
		if (abs(temp_otv - RightAns(i * h))>err)
		{
			err = abs(temp_otv - RightAns(i * h));
		}
		cout << temp_otv << "  " << RightAns(i * h) << "  " << abs(temp_otv - RightAns(i * h)) << endl;
		x += h;
	}
	return err;
}
int main()
{
	//EilerMeth(0.01);
	double h = 0.005;
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
