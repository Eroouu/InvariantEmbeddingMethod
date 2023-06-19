#pragma once
#include<vector>
using namespace std;
class BuildingEq
{
public:
	BuildingEq();
	BuildingEq(double tempP,double tempQ);
	void set_s(double h);
	void set_a(double h);
	void set_y(double h);
	int find_index(double l, double h);
	double r(double l);
	vector<vector<double>> get_y();
protected:
	
private:
	vector<double> vec_s;
	vector<vector<double>> vec_a;
	vector<vector<double>> vec_y;
	double p, q;
};

