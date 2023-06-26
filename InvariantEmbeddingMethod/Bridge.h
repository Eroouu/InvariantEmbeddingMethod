#pragma once
#include<vector>
#include"Base.h"
using namespace std;
class Bridge : public Base
{
public:
	Bridge();
	Bridge(double q_con, double EI_x, double q, double l, double h, double bc_l, double bc_r);
	double r(double x);
	double p(double x);
	double TrueY(double x);
protected:
	
private:
	double q_con;
	double EI_x;
};

