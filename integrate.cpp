#include <iostream>

double exp_func(float x)
{
	return exp(-x);
}

float trap_int(float xmin, float xmax, int nx)
{
	float delx = (xmax - xmin)/nx; 
	float x = xmin;
	float integ = 0;
	while(x < xmax)
	{
		integ += (exp_func(x + delx) + exp_func(x))/2 * delx;
		x += delx;
	}
	return integ;
}

int integrate()
{
	float trap_integral = trap_int(0, 1, 1001);
	TF1 *f1 = new TF1("Exponential", "exp(-x)", 0,  1);
	cout << "Trapezoidal integration result = " << trap_integral << endl;
	cout << "ROOT integration result = " << f1->Integral(0, 1) << endl;
	return 1;
}