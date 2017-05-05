#include <iostream>


float func(float x)
{
	return sin (x);

}

int numdiff()
{
	float x = 0;
	float h = 0.001;
	float diff1 = 1;
	float diff2 = 0;
	cout << sin(2);

	while(diff1 == 0 && diff2 <= 0) 
	{
		diff1 = (sin(x + h) - sin(x - h))/(2*h);
		diff2 = (sin(x + h) + sin(x-h) - 2*sin(x))/(h*h);
		x += 0.01;
	}
	cout << "Max value of sin(x) occurs at x = " << x-0.01 << endl;
	return 1;
}