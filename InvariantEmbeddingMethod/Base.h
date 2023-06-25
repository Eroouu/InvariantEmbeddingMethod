#pragma once
#include<vector>
using namespace std;
class Base
{
public:
	Base();
	Base(double tempQ, double tempL, double tempH);
	void set_s();
	void set_a();
	void set_y();
	void set_all();
	int find_index(double x, double h);
	virtual double r(double x);
	virtual double p(double x);
	vector<vector<double>> get_y();
	vector<double> get_ans();
	virtual double TrueY(double x);
	double get_l();
	double get_h();
	double get_q();
protected:

private:
	vector<double> vec_s;
	vector<vector<double>> vec_a;
	vector<vector<double>> vec_y;
	vector<double> ans;
	double l;
	double h;
	double q;
};

