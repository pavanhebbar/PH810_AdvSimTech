#include <iostream>

double func(double x, double y)
{
	return y;
}

void rk2_int(double xmin, double xmax, double y0, const int n, double y[n])
{
	double h = (double)((xmax - xmin)*1.0/(1.0*n));
	cout << h << endl;
	double x[n];
	y[0] = y0;
	x[0] = xmin;
	for (int i = 1; i < n; i++)
	{
		double k1 = func(x[i-1], y[i-1])*h;
		double k2 = func(x[i-1] + h, y[i-1] + k1)*h;
		y[i] = y[i-1] + 0.5*(k1 + k2);
		x[i] = x[i-1] + h;

	}
}

void rk4_int(double xmin, double xmax, double y0, const int n, double y[n])
{
	double h = (double)((xmax - xmin)*1.0/(1.0*n));
	cout << h << endl;
	double x[n];
	y[0] = y0;
	x[0] = xmin;
	for (int i = 1; i < n; i++)
	{
		double k1 = func(x[i-1], y[i-1])*h;
		double k2 = func(x[i-1] + h/2, y[i-1] + k1/2)*h;
		double k3 = func(x[i-1] + h/2, y[i-1] + k2/2)*h;
		double k4 = func(x[i-1] + h, y[i-1] + k3)*h;
		y[i] = y[i-1] + (k1 + 2*k2 + 2*k3 + k4)/6;
		x[i] = x[i-1] + h;

	}
}


void euler_int(double xmin, double xmax, double y0, const int n, double y[n])
{
	double h = (double)((xmax - xmin)*1.0/(1.0*n));
	cout << h << endl;;
	double x[n];
	y[0] = y0;
	x[0] = xmin;
	for (int i = 1; i < n; i++)
	{
		y[i] = y[i-1] + func(x[i-1], y[i-1])*h;
		x[i] = x[i-1] + h;

	}
}

int int1()
{
	double xmin = 0.0;
	double xmax = 5.0;
	const int n = 10;
	double h = (double)((xmax - xmin)*1.0/(1.0*n));
	double y_euler[n], y_rk2[n], y_rk4[n];
	double x[n];
	x[0] = xmin;
	for (int i = 1; i < n; i++)
	{
		x[i] = x[i-1] + h;
	}
	euler_int(xmin, xmax, 1, n, y_euler);
	rk2_int(xmin, xmax, 1, n, y_rk2);
	rk4_int(xmin, xmax, 1, n, y_rk4);
	TGraph *g1 = new TGraph(n, x, y_euler);
	TGraph *g2 = new TGraph(n, x, y_rk2);
	TGraph *g3 = new TGraph(n, x, y_rk4);
	TF1 *f1 = new TF1("f1", "exp(x)", xmin, xmax);
	TCanvas *c1 = new TCanvas("c1", "Int1", 0, 0, 750, 750);
	g1->Draw();
	g2->Draw("SAME");
	g3 -> Draw("SAME");
	f1->Draw("SAME");
	return 1;
}