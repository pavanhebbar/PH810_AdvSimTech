#include "Integration.cxx"

float func(float x)
{
	return x*x;
}

int Assign2_q2()
{
	Integration I1(-1, 1, 5);
	float integral = I1.GaussQInt1D(func);
	cout << integral << endl;
	return 1;
}