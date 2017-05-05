#include "Integration.h"

Integration::Integration()
{
	_xmin = 0;
	_xmax = 0;
	_ymin = 0;
	_ymax = 0;
	_nx = 0;
	_ny = 0;
}

Integration::Integration(float xmin, float xmax, int nx)
{
	_xmin = xmin;
	_xmax = xmax;
	_ymin = 0;
	_ymax = 0;
	_nx = nx;
	_ny = 0; 
}

Integration::Integration(float xmin, float xmax, float ymin, float ymax, int nx, int ny)
{
	_xmin = xmin;
	_xmax = xmax;
	_ymin = ymin;
	_ymax = ymax;
	_nx = nx;
	_ny = ny;
}

void Integration::Setxrange(float xmin, float xmax)
{
	_xmin = xmin;
	_xmax = xmax;
}

float Integration::Getxmin()
{
	return _xmin;
}

float Integration::Getxmax()
{
	return _xmax;
}

void Integration::Setyrange(float ymin, float ymax)
{
	_ymin = ymin;
	_ymax = ymax;
}

float Integration::Getymin()
{
	return _ymin;
}

float Integration::Getymax()
{
	return _ymax;
}

void Integration::Setnx(int nx)
{
	_nx = nx;
}

void Integration::Setny(int ny)
{
	_ny = ny;
}

int Integration::Getnx()
{
	return _nx;
}

int Integration::Getny()
{
	return _ny;
}

float Integration::TrapInt1D(std::function< float(float) > myfunc1)
{
	double delx = (_xmax - _xmin)/_nx;
	double x = _xmin + delx*0.5;
	double sum = 0.0;
	for(int i = 0; i < _nx; i++)
	{
		sum += myfunc1(x);
		x += delx;
	}
	float integral = (float)(sum*delx);
	return integral;
}

float Integration::TrapInt2D(std::function< float(float, float) > myfunc2)
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
		for(int j = 0; j < _nx; j++)
		{
			sumx += myfunc2(x, y);
			x += delx;
		}
		sumtot += sumx;
		sumx = 0.0;
		y += dely;
	}
	float integral = (float)(sumtot*delx*dely);
	return integral;
}
float Integration::SimpInt1D(std::function< float(float) > myfunc1)
{
	double delx = (_xmax - _xmin)/_nx;
	double x = _xmin + delx*0.5;
	double sum = 0.0;
	for(int i = 0; i < _nx; i++)
	{
		sum += 2*myfunc1(x);
		x += delx;
	}
	x = _xmin + delx;
	for (int i = 0; i < _nx/2; i++)
	{
		sum -= myfunc1(x);
		x += 2*delx;
	}
	float integral = (float)(sum*delx*2.0/3.0);
	return integral;
}

float Integration::SimpInt2D(std::function< float(float, float) > myfunc2)
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

float Integration::RombInt1D(std::function< float(float) > myfunc1, int order, int num = 1)
{
	if(order == 0)
	{
		Integration::Setnx(num);
		return Integration::TrapInt1D(myfunc1);
	}
	else
	{
		float I1, I2;
		I1 = Integration::RombInt1D(myfunc1, order - 1, num);
		I2 = Integration::RombInt1D(myfunc1, order - 1, 2*num);
		float integral = I2 + (I2 - I1)/(pow(4, order) - 1);
		return integral;
	}
}

float Integration::GaussQInt1D(std::function< float(float) > myfunc1)
{
	float integral;
	double x0, x1, x2;
	double t0, t1, t2;
	double c0, c1, c2;
	switch(_nx)
	{
		case 1 :
			t0 = 0;
			c0 = 2;
			t1 = t2 = 0;
			c1 = c2 = 0;
			break;
		case 2 :
			t1 = sqrt(1/3.0);
			c1 = 1;
			t0 = t2 = 0;
			c0 = c2 = 0;
			break;
		case 3 :
			t0 = 0;
			t1 = sqrt(3.0/5.0);
			c0 = 8.0/9.0;
			c1 = 5.0/9.0;
			t2 = c2 = 0;
			break;
		case 4 :
			t1 = sqrt(3.0/7.0 - 2.0/7.0*sqrt(6.0/5.0));
			t2 = sqrt(3.0/7.0 + 2.0/7.0*sqrt(6.0/5.0));
			c1 = (18.0 + sqrt(30.0))/36.0;
			c2 = (18.0 - sqrt(30.0))/36.0;
			t0 = c0 = 0;
			break;
		case 5 :
			t0 = 0;
			t1 = 1.0/3.0*sqrt(5.0 - 2.0*sqrt(10.0/7.0));
			t2 = 1.0/3.0*sqrt(5.0 + 2.0*sqrt(10.0/7.0));
			c0 = 128.0/225.0;
			c1 = (322.0 + 13.0*sqrt(70.0))/900.0;
			c2 = (322.0 - 13.0*sqrt(70.0))/900.0;
			break;
		default :
			cout << "Please set nx smaller than or equal to 5" << endl;
	}
	x0 = _xmax + (_xmax - _xmin)/2*(t0 - 1);
	x1 = _xmax + (_xmax - _xmin)/2*(t1 - 1);
	x2 = _xmax + (_xmax - _xmin)/2*(t2 - 1);
	integral = (float)((_xmax - _xmin)/2 * (c2*myfunc1(-1*x2) + c1*myfunc1(-1*x1) + c0*myfunc1(x0) + c1*myfunc1(x1) + c2*myfunc1(x2)));
	return integral;
}