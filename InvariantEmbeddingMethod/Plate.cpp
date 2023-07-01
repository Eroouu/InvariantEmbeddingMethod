#include "Plate.h"

Plate::Plate()
{
	
	lambda = 2;
	q_v = 20;
	T0 = 0.0;
}

Plate::Plate(double q_v, double lambda, double q, double l, double h):Base(q,l,h)
{
	
	this->lambda = lambda;
	this->q_v = q_v;
	T0 = 100.0;
}

Plate::Plate(double T0, double q_v, double lambda, double q, double l, double h):Base(q,l,h)
{
	this->lambda = lambda;
	this->q_v = q_v;
	this->T0 = T0;
}

double Plate::r(double x)
{
	return 1./x;
}

double Plate::p(double x)
{
	return -q_v / lambda;
}

vector<double> Plate::get_ans()
{
	vector<double> ans;
	vector<vector<double>> y = get_y();
	for (int i = 0; i < y.size(); i++)
	{
		ans.push_back(T0+y[y.size() - 1][i]);
	}
	return ans;
}

double Plate::TrueY(double x)
{
	return T0-q_v * x * x / (2 * lambda) + q_v * l * x / (2 * lambda);
	//return -5 * x * x * x * x / (6 * lambda) + 5 * l * l * l * x / (6 * lambda);
}
