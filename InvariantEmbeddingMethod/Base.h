#pragma once
#include<vector>
using namespace std
class Base
{
public:
	Base();
	Base(double tempQcon, double tempEIx, double tempQ, double tempL, double tempH);
	void set_s();
	void set_a();
	void set_y();
	void set_all();
	int find_index(double x, double h);
	double r(double x);
	double p(double x);
	vector<vector<double>> get_y();
	vector<double> get_ans();
	virtual double TrueY(double x);
protected:

private:
	vector<double> vec_s;
	vector<vector<double>> vec_a;
	vector<vector<double>> vec_y;
	vector<double> ans;
	double q_con;
	double EI_x;
	double q;
	double l;
	double h;
};

