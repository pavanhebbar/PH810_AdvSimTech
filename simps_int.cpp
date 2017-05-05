#include <iostream>

double myfunc2(float x, float y)
{
	return x*y;
}

float simpsons(int _nx, int _ny, float _xmin, float _xmax, float _ymax, float _ymin)
{
	double delx = (_xmax - _xmin)/_nx;
	double dely = (_ymax - _ymin)/_ny;
	double x = _xmin + delx*0.5;
	double y = _ymin + dely*0.5;
	double sumtot = 0.0;
	double sumx = 0.0;
	for(int i = 0; i < _ny; i++)
	{
		x = _xmin + delx*0.5;
		for (int j = 0; j < _nx; j++)
		{
			sumx += 2*myfunc2(x, y);
			x += delx;
		}
		x = _xmin + delx;
		for (int j = 0; j < _nx/2; j++)
		{
			sumx -= myfunc2(x, y);
			x += 2*delx;
		}
		sumtot += 2*sumx;
		sumx = 0;
		y += dely;
	}
	y = _ymin + dely;
	for(int i = 0; i < _ny/2; i++)
	{
		x = _xmin + delx*0.5;
		for (int j = 0; j < _nx; j++)
		{
			sumx += 2*myfunc2(x, y);
			x += delx;
		}
		x = _xmin + delx;
		for (int j = 0; j < _nx/2; j++)
		{
			sumx -= myfunc2(x, y);
			x += 2*delx;
		}
		sumtot -= sumx;
		sumx = 0;
		y += 2*dely;
	}
	float integral = (float)(sumtot*delx*dely*4.0/9.0);
	return integral;
}

int simps_int()
{
	integral = simpsons(10, 10, 0, 10, 10, 0);
	cout << integral << endl;
	TF1 *f1 = new TF1("f1", "1/sqrt(x)", 0, 1);
	cout << f1->Integral(0, 1) << endl;
	return 1;
}