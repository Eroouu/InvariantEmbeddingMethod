#include "BuildingEq.h"
BuildingEq::BuildingEq()
{
	p = 1.;
	q = -1.;
	h = 0.05;
}
BuildingEq::BuildingEq(double tempP, double tempQ, double tempH)
{
	p = tempP;
	q = tempQ;
	h = tempH;
}
void BuildingEq::set_s()
{
	double l = 0;
	for (int i = 0; i < 1 / h + 1; i++)
	{
		if (i == 0)
			vec_s.push_back(0);
		else
		{
			double k1, k2, k3, k4;
			k1 = 1 - vec_s[i - 1] * (1 + r(l));
			k2 = 1 - (vec_s[i - 1] + h / 2 * k1) * (1 + r(l + h / 2));
			k3 = 1 - (vec_s[i - 1] + h / 2 * k2) * (1 + r(l + h / 2));
			k4 = 1 - (vec_s[i - 1] + h * k3) * (1 + r(l + h));
			//vec_s.push_back(vec_s[i-1] + h*(k1 + 2*k2 + 2*k3 + k4) / 6);
			vec_s.push_back(vec_s[i - 1] + h * k1);
		}
		l += h;
	}
}
double BuildingEq::r(double l)
{
	double k = -q;
	return sqrt(k) * (exp(2 * sqrt(k) * l) + 1) / (exp(2 * sqrt(k) * l) - 1);
}
vector<vector<double>> BuildingEq::get_y()
{
	return vec_y;
}
double BuildingEq::TrueY(double x)
{
	double ans = 1. / (-q) * ((1 - exp(q * x / p)) / (exp(q / p) - 1) + x);
	return ans;
}
void BuildingEq::set_a() // l is first, z is second
{
	
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
				temp.push_back(vec_a[i - 1][j] + h * (-r(i * h) * vec_a[i - 1][j]));
		}
		vec_a.push_back(temp);
	}
}

void BuildingEq::set_y()
{
	for (int i = 0; i < 1 / h + 1; i++) // ��� ������������� �������� l 
	{
		vector<double> temp;
		for (int j = 0; j < i + 1; j++) // ��� x �������� ��� l
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
				temp.push_back(vec_y[i - 1][j] - h * vec_s[this->find_index((i-1)*h,h)]*vec_a[this->find_index((i - 1) * h, h)][this->find_index(j*h,h)]); // y_l removed
			}
		}
		vec_y.push_back(temp);
	}
}

void BuildingEq::set_all()
{
	this->set_s();
	this->set_a();
	this->set_y();
}

int BuildingEq::find_index(double l, double h)
{
	int i = 0;
	while (abs(i - l / h) > 1e-5)
	{
		i++;
	}
	return i;
}


