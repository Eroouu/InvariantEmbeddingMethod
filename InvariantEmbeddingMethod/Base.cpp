#include "Base.h"

Base::Base()
{
	q = 0;
	h = 0.05;
	l = 1;
}

Base::Base(double tempQ, double tempL, double tempH)
{
	q = tempQ;
	h = tempH;
	l = tempL;
}

void Base::set_s()
{
	double x = 0;
	for (int i = 0; i < l / h + 1; i++)
	{
		if (i == 0)
			vec_s.push_back(0);
		else
		{
			double k1;// , k2, k3, k4;
			k1 = p(h * i) - vec_s[i - 1] * (q + r(x));
			//k2 = 1 - (vec_s[i - 1] + h / 2 * k1) * (1 + r(l + h / 2));
			//k3 = 1 - (vec_s[i - 1] + h / 2 * k2) * (1 + r(l + h / 2));
			//k4 = 1 - (vec_s[i - 1] + h * k3) * (1 + r(l + h));
			//vec_s.push_back(vec_s[i-1] + h*(k1 + 2*k2 + 2*k3 + k4) / 6);
			vec_s.push_back(vec_s[i - 1] + h * k1);
		}
		x += h;
	}
}

void Base::set_a()
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

void Base::set_y()
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
				temp.push_back(vec_y[i - 1][j] - h * vec_s[this->find_index((i - 1) * h, h)] * vec_a[this->find_index((i - 1) * h, h)][this->find_index(j * h, h)]); // y_l removed
			}
		}
		vec_y.push_back(temp);
	}
}

void Base::set_all()
{
	this->set_s();
	this->set_a();
	this->set_y();
}

int Base::find_index(double x, double h)
{
	int i = 0;
	while (abs(i - x / h) > 1e-5)
	{
		i++;
	}
	return i;
}

double Base::r(double x)
{
	double k = -q;
	//return sqrt(k) * (exp(2 * sqrt(k) * l) + 1) / (exp(2 * sqrt(k) * l) - 1);
	return 1. / x;
}

double Base::p(double x)
{
	return 0.0;
}

vector<vector<double>> Base::get_y()
{
	return vec_y;
}

vector<double> Base::get_ans()
{
	vector<double> ans;
	vector<vector<double>> y = this->get_y();
	for (int i = 0; i < y.size(); i++)
	{
		ans.push_back(y[y.size() - 1][i]);
	}
	return ans;
}

double Base::TrueY(double x)
{
	return 0.0;
}

double Base::get_l()
{
	return l;
}

double Base::get_h()
{
	return h;
}

double Base::get_q()
{
	return q;
}
