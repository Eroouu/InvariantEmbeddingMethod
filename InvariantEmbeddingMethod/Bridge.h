#pragma once
#include<vector>
#include"Base.h"
using namespace std;
class Bridge : public Base
{
public:
	Bridge();
	Bridge(double tempQcon, double tempEIx, double tempQ, double tempL, double tempH);
	double r(double x);
	double p(double x);
	double TrueY(double x);
protected:
	
private:
	double q_con;
	double EI_x;
};

