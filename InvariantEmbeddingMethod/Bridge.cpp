#include "Bridge.h"
Bridge::Bridge()
{
	q_con = 1.;
	EI_x = 1.;
	q = 0;
	h = 0.05;
	l = 1;
}
Bridge::Bridge(double tempQcon, double tempEIx, double tempQ,double tempL, double tempH)
{
	q_con = tempQcon;
	EI_x = tempEIx;
	q = tempQ;
	h = tempH;
	l = tempL;
}
double Bridge::p(double x)
{
	return 1./(EI_x) * (q_con * x * l / 2 - q_con * x * x / 2);
}
void Bridge::set_s()
{
	double x = 0;
	for (int i = 0; i < l / h + 1; i++)
	{
		if (i == 0)
			vec_s.push_back(0);
		else
		{
			double k1;// , k2, k3, k4;
			k1 = p(h*i) - vec_s[i - 1] * (q + r(x));
			//k2 = 1 - (vec_s[i - 1] + h / 2 * k1) * (1 + r(l + h / 2));
			//k3 = 1 - (vec_s[i - 1] + h / 2 * k2) * (1 + r(l + h / 2));
			//k4 = 1 - (vec_s[i - 1] + h * k3) * (1 + r(l + h));
			//vec_s.push_back(vec_s[i-1] + h*(k1 + 2*k2 + 2*k3 + k4) / 6);
			vec_s.push_back(vec_s[i - 1] + h * k1);
		}
		x += h;
	}
}
double Bridge::r(double x)
{
	double k = -q;
	//return sqrt(k) * (exp(2 * sqrt(k) * l) + 1) / (exp(2 * sqrt(k) * l) - 1);
	return 1. / x;
}

vector<vector<double>> Bridge::get_y()
{
	return vec_y;
}
vector<double> Bridge::get_ans()
{
	vector<double> ans;
	vector<vector<double>> y = this->get_y();
	for (int i = 0; i < y.size(); i++)
	{
		ans.push_back(y[y.size() - 1][i]);
	}
	return ans;
}
double Bridge::TrueY(double x)
{
	//double ans = 1. / (-q) * ((1 - exp(q * x / p(x, 1))) / (exp(q / p(x,1)) - 1) + x);
	//double ans = -(1. / 24) * q_con * x * x * x * x / EI_x + l*(1. / 12) * q_con * x * x * x / EI_x - (1. / 24)*l*l*l* q_con * x / EI_x;
	double ans = -(1. / 24) * q_con * (x * x * x * x - 2 * l * x * x * x + l * l * l * x) / EI_x;
	return ans;
}
void Bridge::set_a() // l is first, z is second
{
	
	for (int i = 0; i < l / h + 1; i++)
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

void Bridge::set_y()
{
	for (int i = 0; i < l / h + 1; i++) // для определенного значения l 
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
				temp.push_back(vec_y[i - 1][j] - h * vec_s[this->find_index((i-1)*h,h)]*vec_a[this->find_index((i - 1) * h, h)][this->find_index(j*h,h)]); // y_l removed
			}
		}
		vec_y.push_back(temp);
	}
}

void Bridge::set_all()
{
	this->set_s();
	this->set_a();
	this->set_y();
}

int Bridge::find_index(double x, double h)
{
	int i = 0;
	while (abs(i - x / h) > 1e-5)
	{
		i++;
	}
	return i;
}


