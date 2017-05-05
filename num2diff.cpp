#include <iostream>

float func(float x)
{
	return sin(x);
}

int num2diff()
{
	float x = 0;
	float h = 0.00001;
	float diff1 = 1;
	float diff2 = 0;

	while(diff1 != 0 || diff2 > 0)
	{
		diff1 = (func(x + h) - func(x - h))/(2*h);
		diff2 = (func(x + h) + func(x - h) - 2*func(x))/(h*h);
		x += 0.0001;
	}
	cout << "Max value of sin x is at x = " << x - 0.01 << endl;
	return 1;
}