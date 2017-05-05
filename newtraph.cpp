#include <iostream>

int newraph()
{
	TF1 *f1 = new TF1("f1", "x - cos(x)", 0.01);
	float x_init = 0;
	float x = x_init;
	while(x - cos(x) <= 0.0001)
	{
		x = x - f1(x)/f1->Derivative(x);
	}
	cout << x<< endl;
	return 1;
}