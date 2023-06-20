#pragma once
#include<vector>
class TargettingMethod
{
public:
	TargettingMethod();
	TargettingMethod(double tempQcon, double tempEIx,double tempL, double tempH);
	double TrueY(double x);
	double F(double z, double tempL, double v);
	double FindP();
	double RuK(double tempL, double tempP);
protected:
private:
	double q_con;
	double EI_x;
	double l;
	double h;
	double p;
};

