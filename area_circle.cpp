#include <iostream>

int area_fun(double radius, int nrandom)
{
	TRandom r;
	int n_in = 0;
	for (int i = 0; i < nrandom; i++)
	{
		double x = r.Uniform(-1*radius, radius);
		double y = r.Uniform(-1*radius, radius);
		if (x*x + y*y < radius*radius)
		{
			n_in += 1;
		}
	}
	return n_in;
}

int area_circle()
{
	double radius = 1;
	int nrandom = 100;
	int n_in = area_fun(radius, nrandom);
	double area = (double)n_in*1.0/(nrandom*1.0) *4*radius*radius;
	cout << n_in << endl;
	cout << "Area = " << area << endl;
	return 1;
}