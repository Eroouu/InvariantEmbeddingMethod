#pragma once
#include<vector>
using namespace std;
class BuildingEq
{
public:
	BuildingEq();
	BuildingEq(double tempQcon, double tempEIx, double tempQ, double tempH);
	void set_s();
	void set_a();
	void set_y();
	void set_all();
	int find_index(double l, double h);
	double r(double l);
	double p(double x, double l);
	vector<vector<double>> get_y();
	double TrueY(double x);
protected:
	
private:
	vector<double> vec_s;
	vector<vector<double>> vec_a;
	vector<vector<double>> vec_y;
	double q_con;
	double EI_x;
	double q;
	double h;
};

